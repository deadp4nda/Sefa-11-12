﻿#ifndef MNGFILESERVER_H
#define MNGFILESERVER_H

#include <QTcpServer>

namespace Mongo{
class MngFileSocket;
class MngFileServer : public QTcpServer
{
    Q_OBJECT
public:
    MngFileServer(quint16 port, QObject *parent);
protected:
    void incomingConnection(qintptr handle);
signals:
    void newConnection(MngFileSocket *);
private:
    quint16 port = 0;
};
}
#endif // MNGFILESERVER_H