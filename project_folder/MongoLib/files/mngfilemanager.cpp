#include <QThread>

#include "mngfilemanager.h"
#include "filehansz.h"
#include "mngfilesocket.h"
#include "mngfileserver.h"


namespace Mongo{
MngFileManager::MngFileManager(quint16 port,const QDir &stdDir,  QObject *parent):
    QObject(parent),timer(new QTimer(this)),thread(new QThread(this)),
    saveDir(stdDir),port(port){
    connect(timer,&QTimer::timeout,this,&MngFileManager::updateManager);
}
void MngFileManager::enqueueFile(QFile *file, quint64 type){
    files.enqueue(SafeFileHansz(new FileHansz(*file,type)));
}
void MngFileManager::enqueueFile(SafeFileHansz hansz){
    files.enqueue(hansz);
}

void MngFileManager::createConnection(const QHostAddress &addr, quint16 port){
    if(socket)
        closeConnection();
    address = addr;
    this->port = port;
    socket = new MngFileSocket(addr, port,this);
    if(socket->isValid()){
        socket->moveToThread(thread);
        connect(socket,&MngFileSocket::endedTransmission,this,&MngFileManager::transmissionEnded);
        connect(socket,&MngFileSocket::startedTransmission,this,&MngFileManager::transmissionStarted);
        emit connectionInitiated();
    }else{

        emit connectionFailed();
    }
}
void MngFileManager::closeConnection(){
    if(!socket){
        return;
    }
    delete socket;
    socket = nullptr;
    emit connectionClosed();
}
void MngFileManager::updateManager(){
    if(!busy && !files.isEmpty()){
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
    connect(socket,&MngFileSocket::startedTransmission,this,&MngFileManager::transmissionStarted);
    connect(socket,&MngFileSocket::endedTransmission,this,&MngFileManager::transmissionEnded);
    emit connectionReceived();
}
void MngFileManager::handleClientError(QAbstractSocket::SocketError eCode){
    std::wcerr << "[CLIENT ERROR] (Code = " << eCode <<") : "<< socket->errorString().toStdWString() << std::endl;
}
void MngFileManager::handleServerError(QAbstractSocket::SocketError eCode){
    std::wcerr << "[SERVER ERROR] (Code = " << eCode <<") : "<< server->errorString().toStdWString() << std::endl;
}
}
