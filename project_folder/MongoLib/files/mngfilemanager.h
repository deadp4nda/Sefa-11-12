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
class MngFileSocket;

class MONGOLIBSHARED_EXPORT MngFileManager: public QObject
{
    Q_OBJECT
public:
    MngFileManager(quint16 port = 0,
                            QDir stdDir = QDir(QDir::tempPath()+STD_TEMP_DIR),
                            QObject *parent = nullptr);
    ~MngFileManager();
    void enqueueFile(SafeFileHansz);
    void enqueueFile(QFile *file,quint64);
    void createConnection(const QHostAddress & addr, quint16 port);
    void closeConnection();
signals:
    void fileReceived(SafeFileHansz);
    void fileCancelled(SafeFileHansz);
    void fileReceivingStarted(SafeFileHansz);

    void connectionClosed();
    void connectionInitiated();
    void connectionFailed();
    void connectionReceived();
private:
    QQueue<SafeFileHansz> files;
    QTimer *timer = nullptr;
    MngFileServer *server = nullptr;
    MngFileSocket *socket = nullptr;
    QHostAddress address = QHostAddress(QHostAddress::Null);
    QDir saveDir = QDir::tempPath()+STD_TEMP_DIR;
    quint16 serverPort = 0;
    bool busy = false;
    bool serverActive = false;

private slots:
    void updateManager();
    void sendFile(SafeFileHansz);
    void transmissionStarted(){busy=true;}
    void transmissionEnded(){busy=false;}
    void incomingConnection(MngFileSocket*);
    void handleServerError(QAbstractSocket::SocketError);
    void handleClientError(QAbstractSocket::SocketError);
    void initializeSocket(MngFileSocket *newSocket);
    friend class MngFileSocket;
};
}
#endif // MNGFILEMANAGER_H
