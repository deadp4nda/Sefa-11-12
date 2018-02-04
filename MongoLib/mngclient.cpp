#include "mngclient.h"
#include "mngthmanager.h"
#include "mngserver.h"
#include <QByteArray>
#include <QFile>

namespace Mongo { // Client
MngClient::MngClient(const QHostAddress &toIp, quint16 port, MngThManager *parent):
    QTcpSocket(parent),parentMgr(parent){
    connectToHost(toIp,port);
    waitForConnected();
}
MngClient::MngClient(qintptr handle, MngThManager *parent):
    QTcpSocket(parent),parentMgr(parent){
    setSocketDescriptor(handle);
}
void MngClient::handleReadyRead(){
    QByteArray buffer = readAll();
    if(buffer.size()==0)
        return;
    if(buffer[0]==MONGO_TYPE_EXIT){
        disconnectFromHost();
        waitForDisconnected();
        return;
    }
    if(buffer[0]==MONGO_TYPE_INIT){
        //Handle Init
        return;
    }
}
bool MngClient::sendSomething(DataHansz *data){
    bool success = write(data->getContentBuffer()) == data->getContentBuffer()->size();
    switch(data->getSpec()){
    case MONGO_TYPE_FILE:
        FileHansz *f = (FileHansz*)data;
        delete f;
        break;
    case MONGO_TYPE_INST:
        InstructionHansz *i = (InstructionHansz*)data;
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
