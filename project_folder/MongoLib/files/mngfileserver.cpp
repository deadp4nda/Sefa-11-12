#include "mngfileserver.h"
#include "mngfilesocket.h"

namespace Mongo{
MngFileServer::MngFileServer(quint16 port,const QString &stdDir, QObject *parent):
    QTcpServer(parent), stdDirectory(stdDir), port(port){
    listen(QHostAddress::Any,port);
}
void MngFileServer::incomingConnection(qintptr handle){
    MngFileSocket *sckt = new MngFileSocket(handle,stdDirectory);
    if(sckt->state()==MngFileSocket::ConnectedState)
        emit newConnection(sckt);
}
}
