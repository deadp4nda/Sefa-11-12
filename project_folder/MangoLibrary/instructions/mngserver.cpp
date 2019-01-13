#include "mngserver.h"
#include "mangoconnection.h"
#include "mngthmanager.h"
#include <QTcpServer>

namespace Mango { //Server
MngServer::MngServer(quint16 port, MngThManager *parent):
    QTcpServer(parent),parentMgr(parent){
    listen(QHostAddress::Any,port);
}
void MngServer::incomingConnection(qintptr handle){
    MangoConnection *clnt = new MangoConnection(handle,parentMgr);
    emit newConnection(clnt);
}
}
