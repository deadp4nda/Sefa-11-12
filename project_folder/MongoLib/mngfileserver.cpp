#include "mngfileserver.h"
#include "mongofilesocket.h"
#include "mngfilemanager.h"

namespace Mongo {
MngFileServer::MngFileServer(quint16 listenPort, MngFileManager *parent):QTcpServer(parent){
    listen(QHostAddress::Any,listenPort);
}
void MngFileServer::incomingConnection(qintptr handle){
    MongoFileSocket *fs = new MongoFileSocket(handle);
    std::cout << "Server: Connection Received\n";
    emit newConnection(fs);
}
}
