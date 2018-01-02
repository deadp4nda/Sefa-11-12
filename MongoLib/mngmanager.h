#ifndef MNGMANAGER_H
#define MNGMANAGER_H

#include <QObject>
#include "mongolib.h"

namespace Mongo {
class MONGOLIBSHARED_EXPORT MngManager: public QObject{
    Q_OBJECT
public:
    MngManager(quint16 listenPort = 0,QObject *parent = nullptr);
    void makeConnection(const QHostAddress &addr, quint16 port = 0);
    void closeConnection();
    bool sendInstruction(uchar instr,uint toPrgm, uchar args,QString toFile);
    bool sendFile(QFile &file,uchar filetype);
    quint16 getPeerPort() const;
    QHostAddress getPeerAddr() const;
    quint16 getLocalPort()const;
    QHostAddress getLocalAddr()const;
    quint16 getServerPort()const;
    QHostAddress getServerAddr()const;
public slots:
    void newConnection(MngClient *);
    void handleNewMessage(QByteArray);
signals:
    void message(QByteArray);
    void newMessage(QByteArray);
    void connectionClosed();
    void connectionInitiated();
private:
    MngClient *client = nullptr;
    MngServer *server = nullptr;
private slots:
    void handleServerError(QAbstractSocket::SocketError);
    void handleClientError(QAbstractSocket::SocketError);
};
}
#endif // MNGMANAGER_H
