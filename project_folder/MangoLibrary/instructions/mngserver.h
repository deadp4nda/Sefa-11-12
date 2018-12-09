#ifndef MNGSERVER_H
#define MNGSERVER_H

#include "mangolib_global.h"
#include <QTcpServer>

namespace Mango{
class MngServer: public QTcpServer{
    Q_OBJECT
public:
    MngServer(quint16 port = 0, MngThManager *parent = nullptr);
    MngServer(MngServer&) = delete;
    void incomingConnection(qintptr handle);
signals:
    void newConnection(MangoConnection*);
private:
    MngThManager *parentMgr;
};
}
#endif // MNGSERVER_H
