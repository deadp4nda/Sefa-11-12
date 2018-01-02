#ifndef MNGSERVER_H
#define MNGSERVER_H

#include "mongolib.h"
namespace Mongo{
class MngServer: public QTcpServer{
    Q_OBJECT
public:
    MngServer(quint16 port = 0, MngManager *parent = nullptr);
    MngServer(MngServer&) = delete;
    void incomingConnection(qintptr handle);
signals:
    void newConnection(MngClient*);
private:
    MngManager *parentMgr;
};
}
#endif // MNGSERVER_H
