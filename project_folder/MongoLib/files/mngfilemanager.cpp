#include <QThread>
#include <QDir>

#include "mngfilemanager.h"
#include "filehansz.h"
#include "mngfilesocket.h"
#include "mngfileserver.h"


namespace Mongo{
MngFileManager::MngFileManager(quint16 port,QDir stdDir,  QObject *parent):
    QObject(parent), saveDir(stdDir),port(port){
    thread = new QThread(this);
    timer = new QTimer(this);
    server = new MngFileServer(port,parent);
    connect(timer,&QTimer::timeout,this,&MngFileManager::updateManager);
    connect(server,&MngFileServer::acceptError, this,&MngFileManager::handleServerError);
    timer->setInterval(500);
    timer->start();
}
MngFileManager::~MngFileManager(){
    thread->quit();
    thread->wait();
    if(timer)delete timer;
    if(thread)delete thread;
    if(server)delete server;
    if(socket)delete socket;
}
void MngFileManager::enqueueFile(QFile *file, quint64 type){
    enqueueFile(SafeFileHansz(new FileHansz(*file,type)));
}
void MngFileManager::enqueueFile(SafeFileHansz hansz){
    std::cout << "File Enqueued\n";
    files.enqueue(hansz);
}

void MngFileManager::createConnection(const QHostAddress &addr, quint16 port){
    if(socket)
        closeConnection();
    address = addr;
    this->port = port;
    socket = new MngFileSocket(addr, port);
    if(socket->isValid()){
        socket->moveToThread(thread);
        connect(socket,&MngFileSocket::endedTransmission,this,&MngFileManager::transmissionEnded);
        connect(socket,&MngFileSocket::startedTransmission,this,&MngFileManager::transmissionStarted);
        connect(socket,&MngFileSocket::transmissionCancelled,this, &MngFileManager::FileCancelled);
        thread->start();
        emit connectionInitiated();
    }else{
        emit connectionFailed();
    }
}
void MngFileManager::closeConnection(){
    if(!socket){
        return;
    }
    thread->exit();
    delete socket;
    socket = nullptr;
    emit connectionClosed();
}
void MngFileManager::updateManager(){
    if(!busy && !files.isEmpty() && socket){
        sendFile(files.dequeue());
    }
}
void MngFileManager::sendFile(SafeFileHansz hansz){
    socket->send(hansz);
}
void MngFileManager::incomingConnection(MngFileSocket *sckt){
    if(socket && sckt->isValid()){
        closeConnection();
    }
    socket = sckt;
    socket->moveToThread(thread);
    connect(socket,&MngFileSocket::startedTransmission, this,&MngFileManager::transmissionStarted);
    connect(socket,&MngFileSocket::endedTransmission, this,&MngFileManager::transmissionEnded);
    connect(socket,&MngFileSocket::transmissionCancelled, this, &MngFileManager::FileCancelled);
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(handleClientError(QAbstractSocket::SocketError)));
    emit connectionReceived();
}
void MngFileManager::handleClientError(QAbstractSocket::SocketError eCode){
    std::wcerr << "[CLIENT ERROR] (Code = " << eCode <<") : "<< socket->errorString().toStdWString() << std::endl;
}
void MngFileManager::handleServerError(QAbstractSocket::SocketError eCode){
    std::wcerr << "[SERVER ERROR] (Code = " << eCode <<") : "<< server->errorString().toStdWString() << std::endl;
}
}
