#include "mngfilesocket.h"

namespace Mongo{
MngFileSocket::MngFileSocket(qintptr descr, QObject *parent):
    QTcpSocket(parent){
    setSocketDescriptor(descr);
    connect(this,&MngFileSocket::readyRead,this,&MngFileSocket::handleReadyRead);
}
MngFileSocket::MngFileSocket(const QHostAddress &address, quint16 port, QObject *parent):
    QTcpSocket(parent),addr(address),port(port){
    connectToHost(address,port);
    waitForConnected();
    connect(this,&MngFileSocket::readyRead,this,&MngFileSocket::handleReadyRead);
}
void MngFileSocket::handleReadyRead(){}
void MngFileSocket::send(SafeFileHansz){
    emit startedTransmission();
    emit endedTransmission();
}
}
