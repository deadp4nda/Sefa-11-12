#include "mngclient.h"
#include "mngthmanager.h"
#include "mngserver.h"
#include "datahansz.h"
#include <QByteArray>
#include <QFile>

namespace Mongo { // Client
MngClient::MngClient(const QHostAddress &toIp, quint16 port, MngThManager *parent):
    QTcpSocket(parent),parentMgr(parent){
    connectToHost(toIp,port);
    waitForConnected();
    connect(this, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));
}
MngClient::MngClient(qintptr handle, MngThManager *parent):
    QTcpSocket(parent),parentMgr(parent){
    setSocketDescriptor(handle);
    connect(this, SIGNAL(readyRead()),this,SLOT(handleReadyRead()));
}
void MngClient::handleReadyRead(){
    QByteArray *buffer = new QByteArray(readAll());
    DataHansz *hansz;
    if(buffer->size()==0)
        return;
    switch((uchar)buffer->at(0)){
    case MONGO_TYPE_EXIT:
        disconnectFromHost();
        waitForDisconnected();
        hansz = new DataHansz(buffer);
        break;
    case MONGO_TYPE_INIT:
        hansz = new DataHansz(buffer);
        break;
    case MONGO_TYPE_FILE:
        hansz = new FileHansz(buffer);
        break;
    case MONGO_TYPE_INST:
        hansz = new InstructionHansz(buffer);
        break;
    case MONGO_TYPE_UNSP:
    default:
        hansz = new DataHansz(buffer);
        break;
    }
    emit newMessage(hansz);
}
bool MngClient::sendSomething(DataHansz *data){
    bool success = write(*data->getContentBuffer()) == data->getContentBuffer()->size();
    uchar specifier = data->getSpec();
    FileHansz *f = (FileHansz*)data;
    InstructionHansz *i = (InstructionHansz*)data;
    switch(specifier){
    case MONGO_TYPE_FILE:
        delete f;
        break;
    case MONGO_TYPE_INST:
        delete i;
        break;
    case MONGO_TYPE_INIT:
    case MONGO_TYPE_EXIT:
    case MONGO_TYPE_UNSP:
    default:
        delete data;
    }
    return success;
}
}
