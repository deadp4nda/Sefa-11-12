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
    outSocket = new MongoFileSocket(parentMgr->getPeerAddr(),MONGO_FILE_OUTPORT,this);
    executed = transmissions.dequeue();

    emit execNewFile(executed);
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
    pending.enqueue(socket);
}
}
