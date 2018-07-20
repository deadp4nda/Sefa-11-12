#ifndef MNGFILEMANAGER_H
#define MNGFILEMANAGER_H

#include <QObject>
#include <QQueue>
#include <QTimer>
#include <QThread>
#include <QFile>
#include <QDir>

#include "mongolib_global.h"
#include "filehansz.h"

#define STD_TEMP_DIR "/pinkkarriertesclownsfischbatallion/"

namespace Mongo{
class MngFileServer;
class MngFileSocket;

class MONGOLIBSHARED_EXPORT MngFileManager: public QObject
{
    Q_OBJECT
    enum MongolibError{
        StillFilesToSend,
        NoConnectionToClose,
        StillConnected,
        ConnectionFailed,
        NoRemoteConnectionToClose,
        NoConnectionReceivable
    };
public:
    MngFileManager(quint16 port = 0,
                            QDir stdDir = QDir(QDir::tempPath()+STD_TEMP_DIR),
                            QObject *parent = nullptr);
    ~MngFileManager();

    void setConnectionProperties(QHostAddress foreignHost, quint16 port);
    void forceNewConnection(QHostAddress foreignHost, quint16 port);

public slots:
    void enqueueFile(SafeFileHansz hansz){files.enqueue(hansz);}
    void enqueueFile(QFile *file,quint64 type){enqueueFile(SafeFileHansz(new FileHansz(*file,type)));}
    void closeConnection();

signals:
    void fileReceived(SafeFileHansz);
    void fileCancelled(SafeFileHansz);
    void fileReceivingStarted(SafeFileHansz);
    void sendingStarted(SafeFileHansz);

    void connectionClosed();
    void connectionInitiated();
    void remoteConnectionReceived();
    void remoteConnectionClosed();

    void error(MongolibError);

private:
    QQueue<SafeFileHansz> files;

    QTimer *timer = nullptr;
    MngFileServer *server = nullptr;
    MngFileSocket *sendingSocket = nullptr;
    QThread *sendingThread = nullptr;
    MngFileSocket *receivingSocket = nullptr;
    QThread *receivingThread = nullptr;

    QDir saveDir = QDir::tempPath()+STD_TEMP_DIR;
    bool serverActive = false;
    QHostAddress foreignHost = QHostAddress(QHostAddress::Null);
    quint16 foreignPort = 0;
    quint16 serverPort = 0;

    int createConnection(const QHostAddress & addr, quint16 port);

private slots:
    void closeRemoteConnection();
    void updateManager();
    void incomingConnection(MngFileSocket*);
    void handleServerError(QAbstractSocket::SocketError errorCode);
    void handleSendingClientError(QAbstractSocket::SocketError errorCode);
    void handleReceivingClientError(QAbstractSocket::SocketError errorCode);

    void initializeSendingSocket(MngFileSocket *newSocket);
    void initializeReceivingSocket(MngFileSocket *newSocket);
    void cleanupSendingSocket(MngFileSocket* oldSocket);
    void cleanupReceivingSocket(MngFileSocket *oldSocket);
};
}
#endif // MNGFILEMANAGER_H
