#include "mngserver.h"
#include "mngclient.h"
#include "mngthmanager.h"
#include <QTcpServer>

namespace Mongo { //Server
MngServer::MngServer(quint16 port, MngThManager *parent):
    QTcpServer(parent),parentMgr(parent){
    listen(QHostAddress::Any,port);
}
void MngServer::incomingConnection(qintptr handle){
    MngClient *clnt = new MngClient(handle,parentMgr);
    emit newConnection(clnt);
}
}
