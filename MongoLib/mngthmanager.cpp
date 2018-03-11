#include "mngthmanager.h"
#include "mngserver.h"
#include "mngclient.h"
#include <iostream>
#include <QFile>

#define CONNECT_CLIENT(cl,mgr) QObject::connect(cl,SIGNAL(newFile(FileHansz*)),mgr,SIGNAL(File(FileHansz*)));\
    QObject::connect(cl,SIGNAL(newInstruction(InstructionHansz*)),mgr,SIGNAL(Instruction(InstructionHansz*)));\
    QObject::connect(cl,SIGNAL(newUndefined(DataHansz*)),mgr,SIGNAL(Unknown(DataHansz*)));\
    QObject::connect(cl,SIGNAL(newMessage(DataHansz*)),mgr,SIGNAL(Message(DataHansz*)));

#define CLIENT_VALID(cl) (cl&&cl->isWritable()&&cl->isReadable())
#define DISCONNECT_CLIENT(cl,mgr) QObject::disconnect(cl,SIGNAL(newFile(FileHansz*)),mgr,SIGNAL(File(FileHansz*)));\
    QObject::disconnect(cl,SIGNAL(newInstruction(InstructionHansz*)),mgr,SIGNAL(Instruction(InstructionHansz*)));\
    QObject::disconnect(cl,SIGNAL(newUndefined(DataHansz*)),mgr,SIGNAL(Unknown(DataHansz*)));\
    QObject::disconnect(cl,SIGNAL(newMessage(DataHansz*)),mgr,SIGNAL(Message(DataHansz*)));

namespace Mongo { //Manager
QString MngThManager::standardDir = "";
MngThManager::MngThManager(const QString &stdDir, quint16 listenPort, QObject *parent):
    QObject(parent){
    MngThManager::standardDir = stdDir;
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
        client->sendUndefined(new DataHansz(MONGO_TYPE_INIT));
        CONNECT_CLIENT(client,this);
        emit connectionInitiated();
    }
}
void MngThManager::incomingConnection(MngClient *nClnt){
    qDebug() << "Establishing Communications";
    if(client){
        closeConnection();
    }
    if(nClnt->state() == MngClient::ConnectedState){
        client = nClnt;
        client->sendUndefined(new DataHansz(MONGO_TYPE_INIT));
        CONNECT_CLIENT(client,this);
        emit connectionInitiated();
    }
}
void MngThManager::closeConnection(){
    if(!client)return;
    client->sendUndefined(new DataHansz(MONGO_TYPE_EXIT));
    delete client;
    client = nullptr;
    DISCONNECT_CLIENT(client,this);
    emit connectionClosed();
}
bool MngThManager::sendFile(QFile &file, quint8 filetype){
    if(!CLIENT_VALID(client))
        return false;
    return client->sendFile(new FileHansz(file,filetype));
}
bool MngThManager::sendFile(FileHansz *hansz){
    if(!CLIENT_VALID(client))
        return false;
    return client->sendFile(hansz);
}
bool MngThManager::sendInstruction(quint8 instr, quint32 toPrgm, quint8 args, QByteArray content){
    if(!CLIENT_VALID(client))
        return false;
    return client->sendInstruction(new InstructionHansz(instr,toPrgm,args,&content));
}
bool MngThManager::sendInstruction(InstructionHansz *hansz){
    if(!CLIENT_VALID(client))
        return false;
    return client->sendInstruction(hansz);
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
