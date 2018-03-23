﻿#ifndef MNGMANAGER_H
#define MNGMANAGER_H

#include <QObject>
#include <QDir>
#include "mongolib_global.h"
#include "datahansz.h"

namespace Mongo {
class MongoConnection;
class MONGOLIBSHARED_EXPORT MngThManager: public QObject{
    Q_OBJECT
public:
    MngThManager(const QString &stdDir = QDir::tempPath(), quint16 listenPort = 0,QObject *parent = nullptr);
    void createConnection(const QHostAddress &addr, quint16 port = 0);
    void closeConnection();
    bool sendInstruction(quint8 instr, quint32 toPrgm, quint16 args,
                         const QByteArray &content = QByteArray());
    bool sendFile(QFile &file);
    bool sendHansz(SafeDataHansz hansz);
public: //getter
    quint16 getPeerPort() const;
    QHostAddress getPeerAddr() const;
    quint16 getLocalPort()const;
    QHostAddress getLocalAddr()const;
    quint16 getServerPort()const;
    QHostAddress getServerAddr()const;
    bool isServerActive()const;
    static QString getStandardDirectory();
public slots:
    void incomingConnection(MongoConnection *);
signals:
    void Message(SafeDataHansz);
signals: // connection-based intern signals
    void connectionClosed();
    void connectionInitiated();
private:
    static QString standardDir;
    MongoConnection *client = nullptr;
    MngServer *server = nullptr;
    bool serverActive = false;
private slots:
    void incomingData(const SafeByteArray);
    void handleServerError(QAbstractSocket::SocketError);
    void handleClientError(QAbstractSocket::SocketError);
    friend class MongoConnection;
};
}
#endif // MNGMANAGER_H
