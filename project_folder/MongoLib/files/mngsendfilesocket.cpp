#include "mngsendfilesocket.h"
#include "filehansz.h"
namespace Mongo {
MngSendFileSocket::MngSendFileSocket(const QHostAddress &address, quint16 port,
                             QString stdDir, QObject *parent):
    QTcpSocket(parent),addr(address),sendingPort(port),saveDir(stdDir){
    connectToHost(address,port);
    waitForConnected();
    connect(this, &MngSendFileSocket::readyRead,
            this, &MngSendFileSocket::handleFinishReadyRead);
    connect(this, &MngSendFileSocket::transmitFile,
            this, &MngSendFileSocket::sendFile);
}
MngSendFileSocket::~MngSendFileSocket(){
    disconnect(this, &MngSendFileSocket::readyRead,
            this, &MngSendFileSocket::handleFinishReadyRead);
    disconnect(this, &MngSendFileSocket::transmitFile,
            this, &MngSendFileSocket::sendFile);
    if(!transmissionSuccess){
        emit transmissionCancelled();
    }
    if(state() == QTcpSocket::ConnectedState){
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
        emit transmitFile();
    }else if(bArr == endingOrder()){
        transmissionSuccess = true;
        emit transmissionComplete();
    }
}
void MngSendFileSocket::send(SafeFileHansz hansz){
    current = hansz;
    emit transmissionStarted(current);
    QByteArray test = current->getHeaders();
    ChryHexdump(test,(uint)test.size(),"MngSendFileSocket::send",stderr);
    qint64 written = write(test);
    justWritten(written);
//    qDebug() << "writing: " << written << " Bytes";
    flush();
    waitForBytesWritten(INT_MAX);
}
void MngSendFileSocket::sendFile(){
    QByteArray test;
    QFile* file = current->getFile();
//    Q_ASSERT(file->exists());
    if(!file->isOpen()){
        file->open(QIODevice::ReadOnly);
    }
    file->seek(0);
    while(!file->atEnd()){
        test = file->read(FILE_READ_MAXLENGTH);
        qint64 written = write(test);
        justWritten(written);
    //    qDebug() << "writing: " << written << " Bytes";
    }
}
}
