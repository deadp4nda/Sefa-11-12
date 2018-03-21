#ifndef MONGOCONNECTION_H
#define MONGOCONNECTION_H

#include <QTcpSocket>
#include "mongolib_global.h"
#include <thread>
#include <memory>
#include <QDataStream>

namespace Mongo{
class MongoConnection : public QTcpSocket
{
    Q_OBJECT
public:
    MongoConnection(const QHostAddress &toIp,quint16 port = 0, MngThManager *parent = nullptr);
    MongoConnection(qintptr handle,MngThManager *parent = nullptr);
    bool send(const SafeByteArray);
signals:
    void newInput(const SafeByteArray);
private slots:
    void handleReadyRead();
private:
    MngThManager *parentManager;
    QHostAddress foreignHost;
    quint16 atPort = 0;
    QDataStream stream;
};
}
#endif // MONGOCONNECTION_H
