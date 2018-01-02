#include "mngmanager.h"
#include "mngserver.h"
#include "mngclient.h"
#include <iostream>
#include <QFile>

namespace Mongo { //Manager
MngManager::MngManager(quint16 listenPort, QObject *parent):
    QObject(parent){
    server = new MngServer(listenPort,this);
    connect(server,SIGNAL(newConnection(MngClient*)), this, SLOT(newConnection(MngClient*)));
    connect(server,SIGNAL(acceptError(QAbstractSocket::SocketError)),this,SLOT(handleServerError(QAbstractSocket::SocketError)));
}
void MngManager::makeConnection(const QHostAddress &addr, quint16 port){
    if(client) {
        closeConnection();
    }
    MngClient *tmp = new MngClient(addr,port,this);
    tmp->waitForConnected();
    if(tmp->state() == MngClient::ConnectedState){
        client = tmp;
        client->sendWelcome();
        connect(client, SIGNAL(newMessage(QByteArray)),this, SIGNAL(newMessage(QByteArray)));
        connect(client, SIGNAL(newMessage(QByteArray)), this, SLOT(handleNewMessage(QByteArray)));
        connect(client, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(handleClientError(QAbstractSocket::SocketError)));
    }
}
void MngManager::newConnection(MngClient *nClnt){
    if(client){
        closeConnection();
    }
    if(nClnt->state() == MngClient::ConnectedState){
        client = nClnt;
    }
}
void MngManager::closeConnection(){
    if(!client)return;
    client->sendClose();
    client->close();
    disconnect(client,SIGNAL(newMessage(QByteArray)),this, SIGNAL(newMessage(QByteArray)));
    disconnect(this, SIGNAL(newMessage(QByteArray)), this, SLOT(handleNewMessage(QByteArray)));
    disconnect(client, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(handleClientError(QAbstractSocket::SocketError)));
    delete client;
    client = nullptr;
}
bool MngManager::sendFile(QFile &file, uchar filetype){
    if(!client)
        return false;
    QByteArray buffer;
    buffer.append((uchar)MONGO_TYPE_FILE);
    return client->sendFile(buffer,file,filetype);
}
bool MngManager::sendInstruction(uchar instr, uint toPrgm, uchar args, QString toFile){
    if(!client)
        return false;
    QByteArray buffer;
    buffer.append((uchar)MONGO_TYPE_ISTR);
    return client->sendInstr(buffer,instr,toPrgm,args,toFile);
}
void MngManager::handleNewMessage(QByteArray buffer){
    if(buffer.isEmpty())
        return;
    char *rawArr = buffer.data();
    Mongo_Hdr *header = (Mongo_Hdr*)rawArr;
    if(header->mng_type == MONGO_TYPE_EXIT){
        emit connectionClosed();
        return;
    }
    if(header->mng_type == MONGO_TYPE_WELC){
        emit connectionInitiated();
        return;
    }
    emit message(buffer);
}
quint16 MngManager::getPeerPort() const{
    return client->peerPort();
}
QHostAddress MngManager::getPeerAddr()const{
    return client->peerAddress();
}
quint16 MngManager::getLocalPort()const{
    return client->localPort();
}
QHostAddress MngManager::getLocalAddr()const{
    return client->localAddress();
}
quint16 MngManager::getServerPort()const{
    return server->serverPort();
}
QHostAddress MngManager::getServerAddr()const{
    return server->serverAddress();
}
void MngManager::handleClientError(QAbstractSocket::SocketError){
    std::wcerr << client->errorString().toStdWString() << std::endl;
}
void MngManager::handleServerError(QAbstractSocket::SocketError){
    std::wcerr << server->errorString().toStdWString() << std::endl;
}
}
