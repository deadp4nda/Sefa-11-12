#include "mngfilemanager.h"
#include "mngfilesocket.h"
#include "mngfileserver.h"

namespace Mongo{
MngFileManager::MngFileManager(quint16 port, QDir stdDir, QObject *parent):
    QObject(parent),saveDir(stdDir), serverPort(port){
    if(!saveDir.exists()){
        saveDir.mkpath(saveDir.absolutePath());
    }
    timer = new QTimer(this);
    timer->setInterval(1000);
    server = new MngFileServer(serverPort,stdDir.absolutePath(),this);
    serverActive = server->isListening();
    if(serverActive)qDebug() << "Server active";
    sendingThread = new QThread(this);
    receivingThread = new QThread(this);

    QObject::connect(timer,&QTimer::timeout,this,&MngFileManager::updateManager);
    QObject::connect(server,&MngFileServer::acceptError,this, &MngFileManager::handleServerError);
    QObject::connect(server,&MngFileServer::newConnection,this, &MngFileManager::incomingConnection);

    timer->start();
}

MngFileManager::~MngFileManager(){
    delete timer;
    delete server;
    closeConnection();
    closeRemoteConnection();
}

void MngFileManager::setConnectionProperties(QHostAddress foreignHost, quint16 port){
    if(!files.isEmpty()){
        emit error(StillFilesToSend);
        return;
    }
    this->foreignHost = foreignHost;
    foreignPort = port;
}

void MngFileManager::forceNewConnection(QHostAddress foreignHost, quint16 port){
    closeConnection();
    files.clear();
    this->foreignHost = foreignHost;
    foreignPort = port;
}

void MngFileManager::closeConnection(){
    if(!sendingSocket){
        emit error(NoConnectionToClose);
        return;
    }
    cleanupSendingSocket(sendingSocket);
    delete sendingSocket;
    sendingSocket = nullptr;
    emit connectionClosed();
}

int MngFileManager::createConnection(const QHostAddress &addr, quint16 port){
    if(sendingSocket){
        emit error(StillConnected);
        return 1;
    }
    MngFileSocket *tmp = new MngFileSocket(addr,port,saveDir.absolutePath());
    if(tmp->state() == MngFileSocket::ConnectedState){
        sendingSocket = tmp;
        emit connectionInitiated();
        initializeSendingSocket(sendingSocket);
        return 0;
    }else{
        emit error(ConnectionFailed);
        delete tmp;
        return 2;
    }
}

void MngFileManager::closeRemoteConnection(){
    if(!receivingSocket){
        emit error(NoRemoteConnectionToClose);
        return;
    }
    cleanupReceivingSocket(receivingSocket);
    delete receivingSocket;
    receivingSocket = nullptr;
    emit remoteConnectionClosed();
}
void MngFileManager::updateManager(){
    if(!files.isEmpty() && foreignHost != QHostAddress::Null && !sendingSocket){
        if(createConnection(foreignHost,foreignPort) == 0){
            sendingSocket->send(files.dequeue());
        }
    }
}

void MngFileManager::incomingConnection(MngFileSocket *remoteConnection){
    if(receivingSocket){
        emit error(NoConnectionReceivable);
        remoteConnection->disconnectFromHost();
        delete remoteConnection;
        return;
    }
    initializeReceivingSocket(remoteConnection);
    receivingSocket = remoteConnection;
    initializeReceivingSocket(receivingSocket);
    emit remoteConnectionReceived();
}

void MngFileManager::handleServerError(QAbstractSocket::SocketError errorCode){
    std::wcerr << "\n[SERVER ERROR] Code = " << errorCode << ": " << server->errorString().toStdWString();
}

void MngFileManager::handleReceivingClientError(QAbstractSocket::SocketError errorCode){
    std::wcerr << "\n[RECV. CLIENT ERROR] Code = " << errorCode << ": " << receivingSocket->errorString().toStdWString();
}

void MngFileManager::handleSendingClientError(QAbstractSocket::SocketError errorCode){
    std::wcerr << "\n[SNDNG. CLIENT ERROR] Code = " << errorCode << ": " << sendingSocket->errorString().toStdWString();
}

void MngFileManager::initializeSendingSocket(MngFileSocket *newSocket){
    QObject::connect(newSocket,&MngFileSocket::endedTransmission,
                     this, &MngFileManager::closeConnection);
    QObject::connect(newSocket, SIGNAL(error(QAbstractSocket::SocketError)),
                     this, SLOT(handleSendingClientError(QAbstractSocket::SocketError)));
    QObject::connect(newSocket,&MngFileSocket::startedTransmission,
                     this,&MngFileManager::sendingStarted);
}
void MngFileManager::initializeReceivingSocket(MngFileSocket *newSocket){
    QObject::connect(newSocket,&MngFileSocket::disconnected,
                     this,&MngFileManager::closeRemoteConnection);
    QObject::connect(newSocket,&MngFileSocket::startedReceiving,
                     this,&MngFileManager::fileReceivingStarted);
    QObject::connect(newSocket,&MngFileSocket::transmissionCancelled,
                     this,&MngFileManager::fileCancelled);
    QObject::connect(newSocket,&MngFileSocket::finishedReceiving,
                     this,&MngFileManager::fileReceived);
    QObject::connect(newSocket, SIGNAL(error(QAbstractSocket::SocketError)),
                     this, SLOT(handleReceivingClientError(QAbstractSocket::SocketError)));
}

void MngFileManager::cleanupSendingSocket(MngFileSocket *newSocket){
    QObject::disconnect(newSocket,&MngFileSocket::endedTransmission,
                     this, &MngFileManager::closeConnection);
    QObject::disconnect(newSocket, SIGNAL(error(QAbstractSocket::SocketError)),
                     this, SLOT(handleSendingClientError(QAbstractSocket::SocketError)));
    QObject::disconnect(newSocket,&MngFileSocket::startedTransmission,
                     this,&MngFileManager::sendingStarted);
}

void MngFileManager::cleanupReceivingSocket(MngFileSocket *newSocket){
    QObject::disconnect(newSocket,&MngFileSocket::disconnected,
                     this,&MngFileManager::closeRemoteConnection);
    QObject::disconnect(newSocket,&MngFileSocket::startedReceiving,
                     this,&MngFileManager::fileReceivingStarted);
    QObject::disconnect(newSocket,&MngFileSocket::transmissionCancelled,
                     this,&MngFileManager::fileCancelled);
    QObject::disconnect(newSocket,&MngFileSocket::finishedReceiving,
                     this,&MngFileManager::fileReceived);
    QObject::disconnect(newSocket, SIGNAL(error(QAbstractSocket::SocketError)),
                     this, SLOT(handleReceivingClientError(QAbstractSocket::SocketError)));
}
}
