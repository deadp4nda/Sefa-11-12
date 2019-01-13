#include "mngsendfilesocket.h"
#include "filehansz.h"
namespace Mango {
MngSendFileSocket::MngSendFileSocket(const QHostAddress &address, quint16 port,
                             QString stdDir, QObject *parent):
    QTcpSocket(parent),addr(address),sendingPort(port),saveDir(stdDir){
    connectToHost(address.toString(),port,QIODevice::ReadWrite,address.protocol());
    waitForConnected();
    timer = new QTimer(this);
    timer->setInterval(10);
    connect(this, &MngSendFileSocket::readyRead,
            this, &MngSendFileSocket::handleFinishReadyRead);
    connect(this, &MngSendFileSocket::startNextShot,
            this, &MngSendFileSocket::sendPayload);
}
MngSendFileSocket::~MngSendFileSocket(){
    disconnect(this, &MngSendFileSocket::readyRead,
            this, &MngSendFileSocket::handleFinishReadyRead);
    if(!transmissionSuccess){
        emit transmissionCancelled();
    }
    if(state() == QSslSocket::ConnectedState){
        disconnectFromHost();
        waitForDisconnected();
    }
}
SafeFileHansz MngSendFileSocket::getCurrent(){
    return current;
}
void MngSendFileSocket::handleFinishReadyRead(){
    QByteArray bArr = read(bytesAvailable());
    if(bArr == current->getHeaders()){
//        emit transmitFile();
        file = current->getFile();
        if(!file->isOpen())
            file->open(QIODevice::ReadOnly);
        startNextShot();
    }
}
void MngSendFileSocket::send(SafeFileHansz hansz){
    current = hansz;
    emit transmissionStarted(current);
    QByteArray test = current->getHeaders();
    //ChryHexdump(test,(uint)test.size(),"MngSendFileSocket::send",stderr);
    qint64 written = write(test);
    justWritten(written);
//    qDebug() << "writing: " << written << " Bytes";
    flush();
    waitForBytesWritten(INT_MAX);
}
void MngSendFileSocket::sendPayload() {
    file->seek(0);
    while(!file->atEnd()){
        qint64 written = write(file->read(FILE_READ_MAXLENGTH));
        emit justWritten(written);
    }
    emit transmissionComplete();
}
}
