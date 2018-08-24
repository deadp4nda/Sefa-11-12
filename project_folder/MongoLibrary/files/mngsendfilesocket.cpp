#include "mngsendfilesocket.h"
#include "filehansz.h"
namespace Mongo {
MngSendFileSocket::MngSendFileSocket(const QHostAddress &address, quint16 port,
                             QString stdDir, QObject *parent):
    QTcpSocket(parent),addr(address),sendingPort(port),saveDir(stdDir){
    connectToHost(address,port);
    waitForConnected();
    timer = new QTimer(this);
    timer->setInterval(10);
    connect(this, &MngSendFileSocket::readyRead,
            this, &MngSendFileSocket::handleFinishReadyRead);
    connect(this, &MngSendFileSocket::transmitFile,
            this, &MngSendFileSocket::sendFile);
    connect(timer, &QTimer::timeout,
            this, &MngSendFileSocket::sendNextPortion);
    connect(this, &MngSendFileSocket::startNextShot,
            this, &MngSendFileSocket::prepareNextShot);
}
MngSendFileSocket::~MngSendFileSocket(){
    disconnect(this, &MngSendFileSocket::readyRead,
            this, &MngSendFileSocket::handleFinishReadyRead);
    disconnect(this, &MngSendFileSocket::transmitFile,
            this, &MngSendFileSocket::sendFile);
    disconnect(timer, &QTimer::timeout,
            this, &MngSendFileSocket::sendNextPortion);
    disconnect(this, &MngSendFileSocket::startNextShot,
            this, &MngSendFileSocket::prepareNextShot);
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
//        emit transmitFile();
        file = current->getFile();
        if(!file->isOpen())
            file->open(QIODevice::ReadOnly);
        startNextShot();
    }else if(bArr == endingOrder()){
        transmissionSuccess = true;
        emit transmissionComplete();
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
void MngSendFileSocket::sendFile(){
    QByteArray test;
    file = current->getFile();
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
void MngSendFileSocket::sendNextPortion(){
    timer->stop();
    if(file->atEnd()){
        return;
    }
    QByteArray test = file->read(FILE_READ_MAXLENGTH);
    qint64 written(write(test));
    justWritten(written);
    emit startNextShot();
}
void MngSendFileSocket::prepareNextShot(){
    timer->setSingleShot(true);
    timer->start();
}
}
