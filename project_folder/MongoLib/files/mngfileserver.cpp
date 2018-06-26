#include "mngfileserver.h"
#include "mngfilesocket.h"

namespace Mongo{
MngFileServer::MngFileServer(quint16 port, QObject *parent):
    QTcpServer(parent),port(port){
    listen(QHostAddress::Any,port);
}
void MngFileServer::incomingConnection(qintptr handle){
    MngFileSocket *sckt = new MngFileSocket(handle);
    if(sckt->state()==MngFileSocket::ConnectedState)
        emit newConnection(sckt);
}
}
