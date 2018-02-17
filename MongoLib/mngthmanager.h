#ifndef MNGMANAGER_H
#define MNGMANAGER_H

#include <QObject>
#include "mongolib_global.h"
#include "datahansz.h"

namespace Mongo {
class MONGOLIBSHARED_EXPORT MngThManager: public QObject{
    Q_OBJECT
public:
    MngThManager(quint16 listenPort = 0,QObject *parent = nullptr);
    void createConnection(const QHostAddress &addr, quint16 port = 0);
    void closeConnection();
    bool sendInstruction(quint8 instr, quint32 toPrgm, quint8 args,QByteArray content = QByteArray());
    bool sendInstruction(InstructionHansz *hansz);
    bool sendFile(QFile &file,quint8 filetype);
    bool sendFile(FileHansz *hansz);
public: //getter
    quint16 getPeerPort() const;
    QHostAddress getPeerAddr() const;
    quint16 getLocalPort()const;
    QHostAddress getLocalAddr()const;
    quint16 getServerPort()const;
    QHostAddress getServerAddr()const;
    bool isServerActive()const;

public slots:
    void incomingConnection(MngClient *);
    void handleNewMessage(QByteArray);

signals:
    void message(DataHansz*);   //extern signal
    void newMessage(DataHansz*);
signals: // connection-based intern signals
    void connectionClosed();
    void connectionInitiated();

private:
    MngClient *client = nullptr;
    MngServer *server = nullptr;
    bool serverActive = false;
private slots:
    void handleServerError(QAbstractSocket::SocketError);
    void handleClientError(QAbstractSocket::SocketError);
};
}
#endif // MNGMANAGER_H
