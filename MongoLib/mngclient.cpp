#include "mngclient.h"
#include "mngthmanager.h"
#include "mngserver.h"
#include "datahansz.h"
#include <QByteArray>
#include <QDataStream>
#include <QCoreApplication>
#include <QFile>

namespace Mongo { // Client
MngClient::MngClient(const QHostAddress &toIp, quint16 port, MngThManager *parent):
    QTcpSocket(parent),parentMgr(parent){
    connectToHost(toIp,port);
    waitForConnected();
    connect(this, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));
}
MngClient::MngClient(qintptr handle, MngThManager *parent):
    QTcpSocket(parent),parentMgr(parent){
    setSocketDescriptor(handle);
    connect(this, SIGNAL(readyRead()),this,SLOT(handleReadyRead()));
}
}
