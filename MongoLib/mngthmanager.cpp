#include "mngthmanager.h"
#include "mngserver.h"
#include "mngclient.h"
#include <iostream>
#include <QFile>

#define CLIENT_VALID(cl) (cl&&cl->isWritable()&&cl->isReadable())

namespace Mongo { //Manager
MngThManager::MngThManager(quint16 listenPort, QObject *parent):
    QObject(parent){
    server = new MngServer(listenPort,this);
    connect(server,SIGNAL(newConnection(MngClient*)), this, SLOT(newConnection(MngClient*)));
    connect(server,SIGNAL(acceptError(QAbstractSocket::SocketError)),this,SLOT(handleServerError(QAbstractSocket::SocketError)));
}
void MngThManager::makeConnection(const QHostAddress &addr, quint16 port){
    if(client) {
        closeConnection();
    }
    MngClient *tmp = new MngClient(addr,port,this);
    if(tmp->state() == MngClient::ConnectedState){
        client = tmp;
        client->sendWelcome();
    }
}
void MngThManager::newConnection(MngClient *nClnt){
    if(client){
        closeConnection();
    }
    if(nClnt->state() == MngClient::ConnectedState){
        client = nClnt;
    }
}
void MngThManager::closeConnection(){
    if(!client)return;
    client->sendClose();
    delete client;
    client = nullptr;
}
bool MngThManager::sendFile(QFile &file, quint8 filetype){
    if(!CLIENT_VALID(client))
        return false;
    return client->sendFile(file,filetype);
}
bool MngThManager::sendInstruction(quint8 instr, uint toPrgm, quint8 args, QString toFile){
    if(!CLIENT_VALID(client))
        return false;
    return client->sendInstr(instr,toPrgm,args,toFile);
}
void MngThManager::handleNewMessage(QByteArray buffer){
    if(buffer.isEmpty())
        return;
    char *rawArr = buffer.data();
    Mongo_Hdr *header = (Mongo_Hdr*)rawArr;
    switch(header->mng_type){
    case MONGO_TYPE_EXIT:
        emit message(new DataHansz(&buffer));//dont forget to delete
        emit connectionClosed();
        return;
    case MONGO_TYPE_INIT:
        emit message(new DataHansz(&buffer));//dont forget to delete
        emit connectionInitiated();
        return;
    case MONGO_TYPE_FILE:
        emit message( new FileHansz(&buffer));//dont forget to delete
        return;
    case MONGO_TYPE_INST:
        emit message(new InstructionHansz(&buffer));//dont forget to delete
        return;
    case MONGO_TYPE_UNSP:
    default:
        emit message(new DataHansz(&buffer));//dont forget to delete
    }
}
quint16 MngThManager::getPeerPort() const{
    return client->peerPort();
}
QHostAddress MngThManager::getPeerAddr()const{
    return client->peerAddress();
}
quint16 MngThManager::getLocalPort()const{
    return client->localPort();
}
QHostAddress MngThManager::getLocalAddr()const{
    return client->localAddress();
}
quint16 MngThManager::getServerPort()const{
    return server->serverPort();
}
QHostAddress MngThManager::getServerAddr()const{
    return server->serverAddress();
}
void MngThManager::handleClientError(QAbstractSocket::SocketError){
    std::wcerr << client->errorString().toStdWString() << std::endl;
}
void MngThManager::handleServerError(QAbstractSocket::SocketError){
    std::wcerr << server->errorString().toStdWString() << std::endl;
}
}
