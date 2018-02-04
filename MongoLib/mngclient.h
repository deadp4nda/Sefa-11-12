#ifndef MNGCLIENT_H
#define MNGCLIENT_H
#include <QTcpSocket>
#include "mongolib.h"
namespace Mongo{
class MngClient: public QTcpSocket{
    Q_OBJECT
public:
    MngClient(const QHostAddress &toIp,quint16 port = 0, MngThManager *parent = nullptr);
    MngClient(qintptr handle,MngThManager *parent = nullptr);
    bool sendSomething(DataHansz *);
signals:
    void newMessage(QByteArray);
private slots:
    void handleReadyRead();
private:
    MngThManager *parentMgr;
};
}
#endif // MNGCLIENT_H
