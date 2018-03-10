#include "mngthmanager.h"
#include "mngserver.h"
#include "mngclient.h"
#include <iostream>
#include <QFile>

#define CLIENT_VALID(cl) (cl&&cl->isWritable()&&cl->isReadable())
#define CONNECTCLIENT(cl,th) QObject::connect(cl,SIGNAL(newMessage(DataHansz*)),th,SIGNAL(message(DataHansz*)));
#define DISCONNECTCLIENT(cl,th) QObject::disconnect(cl,SIGNAL(newMessage(DataHansz*)),th,SIGNAL(message(DataHansz*)));

namespace Mongo { //Manager
MngThManager::MngThManager(const QString &stdDir, quint16 listenPort, QObject *parent):
    QObject(parent){
    standardDir = stdDir;
    server = new MngServer(listenPort,this);
    connect(server,SIGNAL(newConnection(MngClient*)), this, SLOT(incomingConnection(MngClient*)));
    connect(server,SIGNAL(acceptError(QAbstractSocket::SocketError)),this,SLOT(handleServerError(QAbstractSocket::SocketError)));
    if(server->isListening()){
        serverActive = true;
    }
}
void MngThManager::createConnection(const QHostAddress &addr, quint16 port){
    if(client) {
        closeConnection();
    }
    MngClient *tmp = new MngClient(addr,port,this);
    if(tmp->state() == MngClient::ConnectedState){
        client = tmp;
        client->sendSomething(new DataHansz(MONGO_TYPE_INIT));
        CONNECTCLIENT(client,this);
        emit connectionInitiated();
    }
}
void MngThManager::incomingConnection(MngClient *nClnt){
    if(client){
        closeConnection();
    }
    if(nClnt->state() == MngClient::ConnectedState){
        client = nClnt;
        client->sendSomething(new DataHansz(MONGO_TYPE_INIT));
        CONNECTCLIENT(client,this);
        emit connectionInitiated();
    }
}
void MngThManager::closeConnection(){
    if(!client)return;
    client->sendSomething(new DataHansz(MONGO_TYPE_EXIT));
    delete client;
    client = nullptr;
    DISCONNECTCLIENT(client,this);
    emit connectionClosed();
}
bool MngThManager::sendFile(QFile &file, quint8 filetype){
    if(!CLIENT_VALID(client))
        return false;
    return client->sendSomething(new FileHansz(file,filetype));
}
bool MngThManager::sendFile(FileHansz *hansz){
    if(!CLIENT_VALID(client))
        return false;
    return client->sendSomething(hansz);
}
bool MngThManager::sendInstruction(quint8 instr, quint32 toPrgm, quint8 args, QByteArray content){
    if(!CLIENT_VALID(client))
        return false;
    return client->sendSomething(new InstructionHansz(instr,toPrgm,args,&content));
}
bool MngThManager::sendInstruction(InstructionHansz *hansz){
    if(!CLIENT_VALID(client))
        return false;
    return client->sendSomething(hansz);
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
    if(CLIENT_VALID(client))
        return client->peerPort();
    else
        return 0;
}
QHostAddress MngThManager::getPeerAddr()const{
    if(CLIENT_VALID(client))
        return client->peerAddress();
    else
        return QHostAddress(QHostAddress::Null);
}
quint16 MngThManager::getLocalPort()const{
    if(CLIENT_VALID(client))
        return client->localPort();
    else
        return 0;
}
QHostAddress MngThManager::getLocalAddr()const{
    if(CLIENT_VALID(client))
        return client->localAddress();
    else
        return QHostAddress(QHostAddress::Null);
}
quint16 MngThManager::getServerPort()const{
    if(server && serverActive)
        return server->serverPort();
    else
        return 0;
}
QHostAddress MngThManager::getServerAddr()const{
    if(server && serverActive)
        return server->serverAddress();
    else
        return QHostAddress(QHostAddress::Null);
}
void MngThManager::handleClientError(QAbstractSocket::SocketError){
    std::wcerr << client->errorString().toStdWString() << std::endl;
}
void MngThManager::handleServerError(QAbstractSocket::SocketError){
    std::wcerr << server->errorString().toStdWString() << std::endl;
    if(!server->isListening())
        serverActive = false;
}
bool MngThManager::isServerActive()const{
    return serverActive;
}
QString MngThManager::getStandardDirectory(){
    return MngThManager::standardDir;
}
}
