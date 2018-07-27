#include "mngfilemanager.h"
#include "mngsendfilesocket.h"
#include "mngrecvfilesocket.h"
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

    QObject::connect(timer,&QTimer::timeout,
                     this,&MngFileManager::updateManager);
    QObject::connect(server,&MngFileServer::acceptError,
                     this, &MngFileManager::handleServerError);
    QObject::connect(server,&MngFileServer::newConnection,
                     this, &MngFileManager::incomingConnection);

    timer->start();
    qDebug() << "SIZEOF RECV: " << sizeof(MngRecvFileSocket);
    qDebug() << "SIZEOF SEND: " << sizeof(MngSendFileSocket);
}
MngFileManager::~MngFileManager(){
    delete timer;
    delete server;
    closeOutgoingConnection();
    closeIncomingConnection();
}
void MngFileManager::lockServer(){
    server->close();
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
    closeOutgoingConnection();
    files.clear();
    this->foreignHost = foreignHost;
    foreignPort = port;
}
void MngFileManager::closeOutgoingConnection(){
    if(!sendingSocket){
        emit error(NoConnectionToClose);
        return;
    }
    cleanupSendingSocket();
//    delete sendingSocket;
    sendingSocket->deleteLater();
    sendingSocket = nullptr;
    emit connectionClosed();
}
void MngFileManager::closeIncomingConnection(){
    if(!receivingSocket){
        emit error(NoConnectionToClose);
        return;
    }
    cleanupReceivingSocket();
//    delete receivingSocket;
    receivingSocket->deleteLater();
    receivingSocket = nullptr;
    server->resumeAccepting();
    emit connectionClosed();
}
int MngFileManager::createConnection(const QHostAddress &addr, quint16 port){
    if(sendingSocket){
        emit error(StillConnected);
        return 1;
    }
    MngSendFileSocket *tmp = new MngSendFileSocket(addr,port,saveDir.absolutePath(), this);
    if(tmp->state() == MngSendFileSocket::ConnectedState){
        sendingSocket = tmp;
        initializeSendingSocket();
        emit connectionInitiated();
        return 0;
    }else{
        emit error(ConnectionFailed);
        delete tmp;
        return 2;
    }
}
void MngFileManager::updateManager(){
    if(!files.isEmpty() && foreignHost != QHostAddress::Null && !sendingSocket){
        if(createConnection(foreignHost,foreignPort) == 0){
            sendingSocket->send(files.dequeue());
        }
    }
}
void MngFileManager::incomingConnection(MngRecvFileSocket *remoteConnection){
    receivingSocket = remoteConnection;
    initializeReceivingSocket();
    emit remoteConnectionReceived();
    server->pauseAccepting();
}
void MngFileManager::handleServerError(QAbstractSocket::SocketError errorCode){
    std::wcerr << "\nFrom " << objectName().toStdWString();
    std::wcerr << "\n[SERVER ERROR] Code = " << errorCode << ": " << server->errorString().toStdWString();
}
void MngFileManager::handleReceivingClientError(QAbstractSocket::SocketError errorCode){
    std::wcerr << "\nFrom " << objectName().toStdWString();
    std::wcerr << "\n[RECV. CLIENT ERROR] Code = " << errorCode << ": " << receivingSocket->errorString().toStdWString();
}
void MngFileManager::handleSendingClientError(QAbstractSocket::SocketError errorCode){
    std::wcerr << "\nFrom " << objectName().toStdWString();
    std::wcerr << "\n[SNDNG. CLIENT ERROR] Code = " << errorCode << ": " << sendingSocket->errorString().toStdWString();
}
void MngFileManager::initializeSendingSocket(){
    MngSendFileSocket *socket = sendingSocket;
    Q_ASSERT(socket != nullptr);
    QObject::connect(socket,&MngSendFileSocket::transmissionComplete,
                     this, &MngFileManager::closeOutgoingConnection);
    QObject::connect(socket,&MngSendFileSocket::transmissionStarted,
                     this,&MngFileManager::fileTransmissionStarted);
    QObject::connect(socket,&MngSendFileSocket::transmissionCancelled,
                     this, &MngFileManager::fileCancelled);
    QObject::connect(socket,&MngSendFileSocket::transmissionComplete,
                     this, &MngFileManager::fileTransmissionEnded);

    QObject::connect(socket,&MngSendFileSocket::transmissionComplete,
                     this, &MngFileManager::closeOutgoingConnection);
    QObject::connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
                     this, SLOT(handleSendingClientError(QAbstractSocket::SocketError)));
}

void MngFileManager::initializeReceivingSocket(){
    MngRecvFileSocket *socket = receivingSocket;
    Q_ASSERT(socket != nullptr);
    QObject::connect(socket,&MngRecvFileSocket::receivingCancelled,
                     this, &MngFileManager::fileCancelled);
    QObject::connect(socket,&MngRecvFileSocket::receivingStarted,
                     this, &MngFileManager::fileReceivingStarted);
    QObject::connect(socket, &MngRecvFileSocket::receivingFinished,
                     this, &MngFileManager::fileSuccessfulReceived);


    QObject::connect(socket,&MngRecvFileSocket::disconnected,
                     this,&MngFileManager::closeIncomingConnection);
    QObject::connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
                     this, SLOT(handleReceivingClientError(QAbstractSocket::SocketError)));
}
void MngFileManager::cleanupSendingSocket(){
    MngSendFileSocket *socket = sendingSocket;
    Q_ASSERT(socket != nullptr);
    QObject::disconnect(socket,&MngSendFileSocket::transmissionComplete,
                     this, &MngFileManager::closeOutgoingConnection);
    QObject::disconnect(socket,&MngSendFileSocket::transmissionStarted,
                     this,&MngFileManager::fileTransmissionStarted);
    QObject::disconnect(socket,&MngSendFileSocket::transmissionCancelled,
                     this, &MngFileManager::fileCancelled);
    QObject::disconnect(socket,&MngSendFileSocket::transmissionComplete,
                     this, &MngFileManager::fileTransmissionEnded);
    QObject::disconnect(socket,&MngSendFileSocket::transmissionComplete,
                     this, &MngFileManager::closeOutgoingConnection);

    QObject::disconnect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
                     this, SLOT(handleSendingClientError(QAbstractSocket::SocketError)));
}
void MngFileManager::cleanupReceivingSocket(){
    MngRecvFileSocket *socket = receivingSocket;
    Q_ASSERT(socket != nullptr);
    QObject::disconnect(socket,&MngRecvFileSocket::receivingCancelled,
                     this, &MngFileManager::fileCancelled);
    QObject::disconnect(socket,&MngRecvFileSocket::receivingStarted,
                     this, &MngFileManager::fileReceivingStarted);
    QObject::disconnect(socket, &MngRecvFileSocket::receivingFinished,
                     this, &MngFileManager::fileSuccessfulReceived);

    QObject::disconnect(socket,&MngRecvFileSocket::disconnected,
                     this,&MngFileManager::closeIncomingConnection);
    QObject::disconnect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
                     this, SLOT(handleReceivingClientError(QAbstractSocket::SocketError)));
}
}
