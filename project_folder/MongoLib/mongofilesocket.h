#ifndef MONGOFILESOCKET_H
#define MONGOFILESOCKET_H

#include <QTcpSocket>
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
    int send(SafeFileHansz);
signals:
    void newFile(const SafeByteArray);
private slots:
    void handleReadyRead();
private:
    quint16 port;
    bool finishedReceiving = false;
    QHostAddress address = QHostAddress(QHostAddress::Null);
    MngFileManager *parentMgr;
    SafeFileHansz incoming = SafeFileHansz(nullptr);
    friend class MngFileManager;
};
}
#endif // MONGOFILESOCKET_H
