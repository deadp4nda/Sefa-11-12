#ifndef MONGOCONNECTION_H
#define MONGOCONNECTION_H

#include <QTcpSocket>
#include "mangolib_global.h"
#include <thread>
#include <memory>
#include <QDataStream>

namespace Mango{
class MangoConnection : public QTcpSocket
{
    Q_OBJECT
public:
    MangoConnection(const QHostAddress &toIp,quint16 port = 0, MngThManager *parent = nullptr);
    MangoConnection(qintptr handle,MngThManager *parent = nullptr);
    bool send(const SafeByteArray);
signals:
    void newInput(const SafeByteArray);
private slots:
    void handleReadyRead();
private:
    QHostAddress foreignHost;
    quint16 atPort = 0;
    QDataStream stream;
    MngThManager *parentManager;
};
}
#endif // MONGOCONNECTION_H
