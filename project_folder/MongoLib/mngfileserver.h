#ifndef MNGFILESERVER_H
#define MNGFILESERVER_H

#include <QTcpServer>

namespace Mongo{
class MongoFileSocket;
class MngFileManager;
class MngFileServer : public QTcpServer
{
    Q_OBJECT
public:
    MngFileServer(quint16 listenPort = 0,MngFileManager *parent = nullptr);
protected:
    void incomingConnection(qintptr handle);
signals:
    void newConnection(MongoFileSocket*);
};
}
#endif // MNGFILESERVER_H
