#include "mngfilesocket.h"
#include <iostream>

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
void MngFileSocket::send(SafeFileHansz hansz){
    emit startedTransmission();
    current = hansz;
    for(int i = 0; i < 20; i++){
        std::cout << "Sending...\n";
    }
    current = nullptr;
    emit endedTransmission();
}
MngFileSocket::~MngFileSocket(){
    if(current){
        emit transmissionCancelled(current);
    }
    disconnectFromHost();
    waitForDisconnected();
    close();
}
}
