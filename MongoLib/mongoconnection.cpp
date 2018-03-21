#include "mongoconnection.h"
#include <QDataStream>
#include <globalAuxilia.h>
#include <mngthmanager.h>
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
    stream >> *array;
    ChryHexdump((uchar*)array->constData(),array->size());
    emit newInput(array);
}
bool MongoConnection::send(const SafeByteArray array){
}
}
