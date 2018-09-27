﻿#include <iostream>
#include <QFile>
#include <QThread>
#include <QTimer>
#include <QQueue>

#include "mngthmanager.h"
#include "mngserver.h"
#include "mongoconnection.h"
#include "instructionhansz.h"

//#define CONNECT_CLIENT(client, manager) QObject::connect(client,&MongoConnection::newInput,manager,&MngThManager::incomingData);

namespace Mongo { //Manager
MngThManager::MngThManager(quint16 listenPort, QObject *parent):
    QObject(parent){
    server = new MngServer(listenPort,this);
    connect(server,SIGNAL(newConnection(MongoConnection*)),
            this, SLOT(incomingConnection(MongoConnection*)));
    connect(server,SIGNAL(acceptError(QAbstractSocket::SocketError)),
            this,SLOT(handleServerError(QAbstractSocket::SocketError)));
    if(server->isListening()){
        serverActive = true;
    }
    timer  = new QTimer(this);
    timer->start(10);
    QObject::connect(timer,&QTimer::timeout,this,&MngThManager::updateManager);
}
MngThManager::~MngThManager(){
    timer->stop();
    if(client)
        closeConnection();
    if(serverActive){
        server->close();
        delete server;
    }
    delete timer;
}
void MngThManager::createConnection(const QHostAddress &addr, quint16 port){
    if(client) {
        closeConnection();
    }
    MongoConnection *tmp = new MongoConnection(addr,port,this);
    tmp->waitForEncrypted();
    if(tmp->state() == MongoConnection::ConnectedState){
        client = tmp;
        address = addr;
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
void MngThManager::sendInstruction(SafeInstruction hansz){
    if(!CLIENT_VALID(client)){
        return;
    }
    client->send(hansz->getAllData());
}
void MngThManager::enqueueInstruction(quint32 instr, quint32 toPrgm, const QByteArray &content, quint32 args){
    instructions.enqueue(SafeInstruction(new InstructionHansz(instr,toPrgm,args,content)));
}
void MngThManager::enqueueInstruction(SafeInstruction inst){
    instructions.enqueue(inst);
}
void MngThManager::incomingData(const SafeByteArray buffer){
    //qDebug() << "Data incoming: "+QString::number(buffer->size())+" Bytes";
    //qDebug() << "Buffer counts: "+QString::number(buffer.use_count())+" Owners";
    lastingTransmission = SafeInstruction(new InstructionHansz(buffer));
    emit Message(lastingTransmission);
}
void MngThManager::updateManager(){
    if(!instructions.isEmpty()){
        this->sendInstruction(instructions.dequeue());
    }
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
