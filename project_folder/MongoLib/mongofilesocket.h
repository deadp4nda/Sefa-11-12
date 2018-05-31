#ifndef MONGOFILESOCKET_H
#define MONGOFILESOCKET_H

#include <QTcpSocket>
#include <QThread>
#include "mongolib_global.h"
#include "filehansz.h"

namespace Mongo{
class MngFileManager;
class MongoFileSocket : public QTcpSocket
{
    Q_OBJECT
public:
    MongoFileSocket(const QHostAddress &toIp, quint16 port = 0, MngFileManager *parent = nullptr);
    MongoFileSocket(qintptr handle,MngFileManager *parent = nullptr);
    MongoFileSocket(const MongoFileSocket&) = delete;
    void send(SafeFileHansz);
    void setStdDir(QDir nDir){dir = nDir;}
signals:
    void newFile(const SafeByteArray);
protected slots:
    void run();
private:
    QDir dir = QDir::temp();
    quint16 port;
    bool finishedReceiving = false;
    QHostAddress address = QHostAddress(QHostAddress::Null);
    MngFileManager *parentMgr = nullptr;
    SafeFileHansz incoming = SafeFileHansz(nullptr);
    friend class MngFileManager;
};
}
#endif // MONGOFILESOCKET_H
