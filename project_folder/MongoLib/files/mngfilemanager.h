﻿#ifndef MNGFILEMANAGER_H
#define MNGFILEMANAGER_H

#include <QObject>
#include <QQueue>
#include <QTimer>
#include <QFile>
#include <QDir>

#include "mongolib_global.h"

namespace Mongo{
class MngFileServer;
class MngFileSocket;
class MngFileManager: public QObject
{
    Q_OBJECT
public:
    explicit MngFileManager(quint16 port = 0,
                            const QDir& stdDir = QDir::tempPath()+"/pinkkarriertesclownsfischbatallion/",
                            QObject *parent = nullptr);
    void enqueueFile(SafeFileHansz);
    void enqueueFile(QFile *file,quint64);
    void createConnection(const QHostAddress & addr, quint16 port);
    void closeConnection();
signals:
    void FileIncoming(SafeFileHansz);
    void FileReceived(SafeFileHansz);
    void connectionClosed();
    void connectionInitiated();
    void connectionFailed();
    void connectionReceived();
private:
    QQueue<SafeFileHansz> files;
    QTimer *timer = nullptr;
    QThread *thread = nullptr;
    MngFileServer *server = nullptr;
    MngFileSocket *socket = nullptr;
    QHostAddress address = QHostAddress(QHostAddress::Null);
    QDir saveDir = QDir::tempPath()+"/pinkkarriertesclownsfischbatallion/";
    quint16 port = 0;
    bool busy = false;
private slots:
    void updateManager();
    void sendFile(SafeFileHansz);
    void transmissionStarted(){busy=true;}
    void transmissionEnded(){busy=false;}
    void incomingConnection(MngFileSocket*);
    void handleServerError(QAbstractSocket::SocketError);
    void handleClientError(QAbstractSocket::SocketError);
    friend class MngFileSocket;
};
}
#endif // MNGFILEMANAGER_H
