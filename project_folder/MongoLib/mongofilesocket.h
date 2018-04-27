#ifndef MONGOFILESOCKET_H
#define MONGOFILESOCKET_H

#include <QTcpSocket>
#include "mongolib_global.h"
#include "filehansz.h"

namespace Mongo{
class MongoFileSocket : public QTcpSocket
{
    Q_OBJECT
public:
    MongoFileSocket(const QHostAddress &toIp, SafeFileHansz fileH, quint16 port = 0, MngThManager *parent = nullptr);
    MongoFileSocket(qintptr handle,MngThManager *parent = nullptr);
    MongoFileSocket(const MongoFileSocket&) = delete;
    bool send();
    bool transmitting()const{return (bool)fileH;}
signals:
    void newFile(const SafeByteArray);
private slots:
    void handleReadyRead();
private:
    quint16 port;
    MngThManager *parentMgr;
    SafeFileHansz fileH;
};
}
#endif // MONGOFILESOCKET_H
