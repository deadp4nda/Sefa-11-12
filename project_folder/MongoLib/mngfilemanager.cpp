#include "mngfilemanager.h"

#include "mngfileserver.h"
#include "mongofilesocket.h"
#include "mngthmanager.h"

namespace Mongo {
MngFileManager::MngFileManager(QDir stdDir,MngThManager *parent):
    parentMgr(parent), dir(stdDir){
    timer = new QTimer(this);
    timer->start(2000);
    server = new MngFileServer(MONGO_FILE_INPORT,this);
    connect(server,&MngFileServer::newConnection,this,&MngFileManager::receiveNewConnection);
    connect(timer,&QTimer::timeout,this,&MngFileManager::checkMate);
}
void MngFileManager::checkMate(){
    if(!executed && !(transmissions.isEmpty())){
        run();
    }
    for(MongoFileSocket*s:pending){
        if(!s->isWritable()){
            emit newFileReceived(s->incoming);
            pending.removeAll(s);
        }
    }
}
void MngFileManager::addFile(SafeFileHansz hansi){
    transmissions.enqueue(hansi);
}
void MngFileManager::run(){
    outSocket = new MongoFileSocket(parentMgr->address,MONGO_FILE_INPORT,this);
    executed = transmissions.dequeue();

    emit processNewFile(executed);
    outSocket->send(executed);
    outSocket->disconnectFromHost();
    outSocket->waitForDisconnected();
    outSocket->close();
    emit sendingFinished(executed);

    executed = SafeFileHansz(nullptr);
    delete outSocket;
    outSocket = nullptr;
}
void MngFileManager::receiveNewConnection(MongoFileSocket *socket){
//    socket->setStdDir(dir);
    pending.enqueue(socket);
}
MngFileManager::~MngFileManager(){
    for(SafeFileHansz h:transmissions){
        emit transmissionCancelled(h);
    }
    transmissions.clear();
    if(inSocket)delete inSocket;
    if(outSocket)delete outSocket;
    if(timer)delete timer;
    if(server)delete server;
    for(MongoFileSocket*s:pending){
        delete s;
    }
}
}
