#include <iostream>
#include <QFile>
#include <QThread>

#include "mngthmanager.h"
#include "mngserver.h"
#include "mongoconnection.h"
#include "instructionhansz.h"
#include "mongofilesocket.h"

//#define CONNECT_CLIENT(client, manager) QObject::connect(client,&MongoConnection::newInput,manager,&MngThManager::incomingData);

namespace Mongo { //Manager
QString MngThManager::standardDir = "";
MngThManager::MngThManager(const QString &stdDir, quint16 listenPort, QObject *parent):
    QObject(parent){
    MngThManager::standardDir = stdDir;
    server = new MngServer(listenPort,this);
    connect(server,SIGNAL(newConnection(MongoConnection*)),
            this, SLOT(incomingConnection(MongoConnection*)));
    connect(server,SIGNAL(acceptError(QAbstractSocket::SocketError)),
            this,SLOT(handleServerError(QAbstractSocket::SocketError)));
    if(server->isListening()){
        serverActive = true;
    }
}
MngThManager::~MngThManager(){
    if(client)
        closeConnection();
    if(serverActive){
        server->close();
        delete server;
    }
}
void MngThManager::createConnection(const QHostAddress &addr, quint16 port){
    if(client) {
        closeConnection();
    }
    MongoConnection *tmp = new MongoConnection(addr,port,this);
    if(tmp->state() == MongoConnection::ConnectedState){
        client = tmp;
        emit connectionInitiated();
    }
}
void MngThManager::incomingConnection(MongoConnection *nClnt){
    if(client){
        closeConnection();
    }
    if(nClnt->state() == MongoConnection::ConnectedState){
        client = nClnt;
        emit connectionInitiated();
    }
}
void MngThManager::closeConnection(){
    if(!client)return;
    sendInstruction(SafeInstruction(new InstructionHansz(Instructions::Exit)));
    client->abort();
    //disconnect client
    delete client;
    client = nullptr;
    emit connectionClosed();
}
bool MngThManager::sendInstruction(SafeInstruction hansz){
    if(!CLIENT_VALID(client)){
        return false;
    }
    return client->send(hansz->getAllData());
}
bool MngThManager::sendInstruction(quint32 instr, quint32 toPrgm, const QByteArray &content, quint32 args){
    return sendInstruction(SafeInstruction(new InstructionHansz(instr,toPrgm,args,content)));
}
bool MngThManager::sendFile(QFile &file, quint64 type){
    fileManager->addFile(SafeFileHansz(new FileHansz(file,type)));
    return true;
}
void MngThManager::incomingData(const SafeByteArray buffer){
//    qDebug() << "Data incoming: "+QString::number(buffer->size())+" Bytes";
//    qDebug() << "Buffer counts: "+QString::number(buffer.use_count())+" Owners";
    lastingTransmission = SafeInstruction(new InstructionHansz(buffer));
    emit Message(lastingTransmission);
}
void MngThManager::handleClientError(QAbstractSocket::SocketError){
    std::wcerr << client->errorString().toStdWString() << std::endl;
}
void MngThManager::handleServerError(QAbstractSocket::SocketError){
    std::wcerr << server->errorString().toStdWString() << std::endl;
    if(!server->isListening())
        serverActive = false;
}
quint16 MngThManager::getServerPort()const{
    return (server && serverActive)?(server->serverPort()): 0;
}
QHostAddress MngThManager::getServerAddr()const{
    return (server && serverActive)?(server->serverAddress()):QHostAddress(QHostAddress::Null);
}
}
