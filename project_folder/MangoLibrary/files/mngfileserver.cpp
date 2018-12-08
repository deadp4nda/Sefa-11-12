#include "mngfileserver.h"
#include "mngrecvfilesocket.h"

namespace Mango{
MngFileServer::MngFileServer(quint16 port,const QString &stdDir, QObject *parent):
    QTcpServer(parent), stdDirectory(stdDir), port(port){
    listen(QHostAddress::Any,port);
}
void MngFileServer::incomingConnection(qintptr handle){
    MngRecvFileSocket *sckt = new MngRecvFileSocket(handle,stdDirectory);
    if(sckt->state()==MngRecvFileSocket::ConnectedState)
        emit newConnection(sckt);
}
}
