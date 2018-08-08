﻿#ifndef MNGFILESERVER_H
#define MNGFILESERVER_H

#include <QTcpServer>

namespace Mongo{

class MngRecvFileSocket;

class MngFileServer : public QTcpServer
{
    Q_OBJECT
public:
    MngFileServer(quint16 port, const QString &stdDir, QObject *parent);
protected:
    void incomingConnection(qintptr handle);
signals:
    void newConnection(MngRecvFileSocket *);
private:
    QString stdDirectory;
    quint16 port = 0;
};
}
#endif // MNGFILESERVER_H
