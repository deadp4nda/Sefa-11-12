#include "mngfilemanager.h"

#include "mngfileserver.h"
#include "mongofilesocket.h"
#include "mngthmanager.h"

namespace Mongo {
MngFileManager::MngFileManager(MngThManager *parent):
    parentMgr(parent){
    timer = new QTimer(this);
    timer->start(2000);
}
void MngFileManager::checkMate(){
    if(!executed && !(transmissions.isEmpty())){
        executing();
    }
}
void MngFileManager::addFile(SafeFileHansz hansi){
    transmissions.enqueue(hansi);
}
int MngFileManager::executing(){
    socket = new MongoFileSocket(parentMgr->getPeerAddr(),0,this);
    transmissionThread = new QThread(this);
    executed = transmissions.dequeue();
    socket->moveToThread(transmissionThread);

    emit execNewFile(executed);
    int exitCode = socket->send(executed);

    executed = SafeFileHansz(nullptr);
    delete socket;
    delete transmissionThread;
    return exitCode;
}
void MngFileManager::setupServer(quint16 listeningPort){
    server = new MngFileServer(listeningPort,this);
    connect(server,&MngFileServer::newConnection,this,&MngFileManager::receiveNewConnection);
}
void MngFileManager::receiveNewConnection(MongoFileSocket *){

}
}
