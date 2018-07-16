#include <QThread>
#include <QDir>

#include "mngfilemanager.h"
#include "filehansz.h"
#include "mngfilesocket.h"
#include "mngfileserver.h"

namespace Mongo{
MngFileManager::MngFileManager(quint16 port, QDir stdDir, QObject *parent):
    QObject(parent), saveDir(stdDir),serverPort(port){
    timer = new QTimer(this);
    server = new MngFileServer(serverPort,saveDir.absolutePath(),parent);
    connect(server,&MngFileServer::acceptError, this,&MngFileManager::handleServerError);
    connect(server, &MngFileServer::newConnection,this, &MngFileManager::incomingConnection);
    if(server->isListening()){
        qDebug() << "Server listening!";
        serverActive = true;
    }
    timer->start(1000);
    connect(timer,&QTimer::timeout,this,&MngFileManager::updateManager);
}
MngFileManager::~MngFileManager(){
    delete timer;
    delete server;
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
    if(socket){
        closeConnection();
    }
    MngFileSocket *tmp = new MngFileSocket(addr, port, saveDir.absolutePath());
    if(tmp->state() == MngFileSocket::ConnectedState){
        address = addr;
        this->serverPort = port;
        initializeSocket(tmp);
        emit connectionInitiated();
    }
}
void MngFileManager::closeConnection(){
    if(!socket){
        return;
    }
    disconnect(socket,&MngFileSocket::startedTransmission, this,&MngFileManager::transmissionStarted);
    disconnect(socket,&MngFileSocket::endedTransmission, this,&MngFileManager::transmissionEnded);
    disconnect(socket,&MngFileSocket::transmissionCancelled, this, &MngFileManager::fileCancelled);
    disconnect(socket,&MngFileSocket::startedReceiving,this, &MngFileManager::fileReceivingStarted);
    disconnect(socket, &MngFileSocket::finishedReceiving,this, &MngFileManager::fileReceived);
    disconnect(socket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,  SLOT(handleClientError(QAbstractSocket::SocketError)));
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
    if(socket){
        closeConnection();
    }
    if(sckt->state() == MngFileSocket::ConnectedState){
        initializeSocket(sckt);
        emit connectionReceived();
    }
}
void MngFileManager::handleClientError(QAbstractSocket::SocketError eCode){
    std::wcerr << "[CLIENT ERROR] (Code = " << eCode <<") : "<< socket->errorString().toStdWString() << std::endl;
}
void MngFileManager::handleServerError(QAbstractSocket::SocketError eCode){
    std::wcerr << "[SERVER ERROR] (Code = " << eCode <<") : "<< server->errorString().toStdWString() << std::endl;
}
void MngFileManager::initializeSocket(MngFileSocket* newSocket){
    socket = newSocket;
    connect(socket,&MngFileSocket::startedTransmission, this,&MngFileManager::transmissionStarted);
    connect(socket,&MngFileSocket::endedTransmission, this,&MngFileManager::transmissionEnded);
    connect(socket,&MngFileSocket::transmissionCancelled, this, &MngFileManager::fileCancelled);
    connect(socket,&MngFileSocket::startedReceiving,this, &MngFileManager::fileReceivingStarted);
    connect(socket, &MngFileSocket::finishedReceiving,this, &MngFileManager::fileReceived);
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,  SLOT(handleClientError(QAbstractSocket::SocketError)));
}
}
