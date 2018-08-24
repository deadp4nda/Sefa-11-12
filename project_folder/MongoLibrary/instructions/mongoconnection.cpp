#include "mongoconnection.h"
#include <QDataStream>
#include "../instructions/mngthmanager.h"
#include <iostream>

namespace Mongo{
MongoConnection::MongoConnection(const QHostAddress &toIp, quint16 port, MngThManager *parent):
    QTcpSocket(parent),foreignHost(toIp),atPort(port),parentManager(parent){
    connectToHost(foreignHost,port);
    waitForConnected();
    connect(this,SIGNAL(readyRead()),this,SLOT(handleReadyRead()));
    stream.setDevice(this);
}
MongoConnection::MongoConnection(qintptr handle, MngThManager *parent):
    QTcpSocket(parent),parentManager(parent){
    setSocketDescriptor(handle);
    connect(this, SIGNAL(readyRead()),this,SLOT(handleReadyRead()));
    stream.setDevice(this);
}
void MongoConnection::handleReadyRead(){
    SafeByteArray array(new QByteArray);
    qint64 available = bytesAvailable();
//    std::cerr << available << "\n";
    quint8 byte;
    for(int i = 0; i < available; i++){
        stream >> byte;
        array->append(byte);
    }
    parentManager->incomingData(array);

}
bool MongoConnection::send(const SafeByteArray array){
    return stream.writeRawData(array->constData(),array->length()) == array->size();
}
}
