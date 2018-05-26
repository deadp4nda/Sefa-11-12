#include "mongofilesocket.h"
#include "filehansz.h"
#include <iostream>

namespace Mongo {
MongoFileSocket::MongoFileSocket(const QHostAddress &toIp, quint16 port, MngFileManager *parent):
port(port),parentMgr(parent),address(toIp){
    connectToHost(toIp,port);
    waitForConnected();
    connect(this,&MongoFileSocket::readyRead,this,&MongoFileSocket::handleReadyRead);
    finishedReceiving = true;
}
MongoFileSocket::MongoFileSocket(qintptr handle, MngFileManager *parent):
    parentMgr(parent){
    setSocketDescriptor(handle);
}
void MongoFileSocket::send(SafeFileHansz hansz){
    write(hansz->getHeaders());
    QFile *device = hansz->getFile();
    while(!device->atEnd()){
        quint64 written = write(device->read(FILE_READ_MAXLENGTH));
        qDebug() << "write " << (quint64)written << " Bytes";
        if(!written){
            qDebug() << "ERROR while writing to output stream: Stream corrupted";
        }
    }
}
void MongoFileSocket::handleReadyRead(){
    SafeByteArray array = SafeByteArray(new QByteArray);
    *array = read(bytesAvailable());
    if(!incoming){
        incoming = SafeFileHansz(new FileHansz(array,dir));
    }else{
        incoming->addData(array);
    }
}

}
