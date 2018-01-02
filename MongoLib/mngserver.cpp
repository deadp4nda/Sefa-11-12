#include "mngserver.h"
#include "mngclient.h"
#include "mngmanager.h"
#include <QTcpServer>

namespace Mongo { //Server
MngServer::MngServer(quint16 port, MngManager *parent):
    QTcpServer(parent),parentMgr(parent){
    listen(QHostAddress::Any,port);
}
void MngServer::incomingConnection(qintptr handle){
    MngClient *clnt = new MngClient(handle,parentMgr);
    emit newConnection(clnt);
}
}
