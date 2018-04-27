#include "mongofilesocket.h"
#include "datahansz.h"
#include <iostream>

namespace Mongo {
MongoFileSocket::MongoFileSocket(const QHostAddress &toIp, SafeFileHansz  fileH, quint16 port, MngThManager *parent):
port(port),parentMgr(parent),fileH(fileH){
    connectToHost(toIp,port);
    waitForConnected();
    connect(this,&MongoFileSocket::readyRead,this,&MongoFileSocket::handleReadyRead);
}
MongoFileSocket::MongoFileSocket(qintptr handle, MngThManager *parent):
    parentMgr(parent){
    setSocketDescriptor(handle);
}
bool MongoFileSocket::send(){

    return false;
}
void MongoFileSocket::handleReadyRead(){
    SafeByteArray array(new QByteArray(read(bytesAvailable())));
    fileH->addData(array);
}
}
