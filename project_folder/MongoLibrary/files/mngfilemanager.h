#ifndef MNGFILEMANAGER_H
#define MNGFILEMANAGER_H

#include <QObject>
#include <QQueue>
#include <QTimer>
#include <QThread>
#include <QFile>
#include <QDir>

#include "mongolib_global.h"

#define STD_TEMP_DIR "/pinkkarriertesclownsfischbatallion/"

namespace Mongo{
class MngFileServer;
class MngSendFileSocket;
class MngRecvFileSocket;
class FileHansz;

class /*MONGOLIBSHARED_EXPORT*/ MngFileManager: public QObject
{
    Q_OBJECT
    enum MongolibError{
        StillFilesToSend,
        NoConnectionToClose,
        StillConnected,
        ConnectionFailed,
        NoRemoteConnectionToClose,
        NoConnectionReceivable,
        FileInvalid
    };
public:
    MngFileManager(quint16 port = 0,
                            QDir stdDir = QDir(QDir::tempPath()+STD_TEMP_DIR),
                            QObject *parent = nullptr);
    ~MngFileManager();
    void lockServer();
    void setConnectionProperties(QHostAddress foreignHost, quint16 port);
    void forceNewConnection(QHostAddress foreignHost, quint16 port);
public slots:
    void activate();
    void enqueueFile(SafeFileHansz hansz);
    void enqueueFile(QFile *file,quint64 type);
    void closeOutgoingConnection();
    void closeIncomingConnection();
signals:
    void fileReceivingStarted(SafeFileHansz);
    void fileSuccessfulReceived();
    void fileTransmissionStarted(SafeFileHansz);
    void fileTransmissionEnded();

    void fileCancelled();

    void connectionClosed();
    void connectionInitiated();
    void remoteConnectionReceived();
    void remoteConnectionClosed();

    void error(MongolibError);
    void justSent(qint64);
    void justReceived(qint64);
    void noFilesToSend();
private:
    QQueue<SafeFileHansz> files;

    QTimer *timer = nullptr;
    MngFileServer *server = nullptr;
    MngSendFileSocket *sendingSocket = nullptr;
//    QThread *sendingThread = nullptr;
    MngRecvFileSocket *receivingSocket = nullptr;
//    QThread *receivingThread = nullptr;

    QDir saveDir = QDir::tempPath()+STD_TEMP_DIR;
    bool serverActive = false;
    QHostAddress foreignHost = QHostAddress::Null;
    quint16 foreignPort = 0;
    quint16 serverPort = 0;

    int createConnection(const QHostAddress & addr, quint16 port);

private slots:
    void updateManager();
    void incomingConnection(MngRecvFileSocket*);
    void handleServerError(QAbstractSocket::SocketError errorCode);
    void handleSendingClientError(QAbstractSocket::SocketError errorCode);
    void handleReceivingClientError(QAbstractSocket::SocketError errorCode);

    void initializeSendingSocket();
    void initializeReceivingSocket();
    void cleanupSendingSocket();
    void cleanupReceivingSocket();
};
}
#endif // MNGFILEMANAGER_H
