#include "mngfilemanager.h"
#include "filehansz.h"
#include "mngfilesocket.h"

namespace Mongo{
MngFileManager::MngFileManager(const QDir &stdDir, quint16 port, QObject *parent):
    QObject(parent),timer(new QTimer(this)),saveDir(stdDir),port(port){
    connect(socket,&MngFileSocket::startedTransmission,this,&MngFileManager::transmissionStarted);
    connect(socket,&MngFileSocket::endedTransmission,this,&MngFileManager::transmissionEnded);
}
void MngFileManager::updateManager(){}
void MngFileManager::sendFile(SafeFileHansz){}
void MngFileManager::enqueueFile(QFile *file, quint64 type){
    files.enqueue(SafeFileHansz(new FileHansz(*file,type)));
}
void MngFileManager::enqueueFile(SafeFileHansz hansz){
    files.enqueue(hansz);
}
void MngFileManager::sendFile(SafeFileHansz hansz){}
}
