#include "mngserver.h"
#include "mongoconnection.h"
#include "mngthmanager.h"
#include <QTcpServer>

namespace Mongo { //Server
MngServer::MngServer(quint16 port, MngThManager *parent):
    QTcpServer(parent),parentMgr(parent){
    listen(QHostAddress::Any,port);
}
void MngServer::incomingConnection(qintptr handle){
    MongoConnection *clnt = new MongoConnection(handle,parentMgr);
    emit newConnection(clnt);
}
}
