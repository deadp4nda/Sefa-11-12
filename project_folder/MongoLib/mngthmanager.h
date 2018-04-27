#ifndef MNGMANAGER_H
#define MNGMANAGER_H

#include <QObject>
#include <QDir>
#include <QThread>
#include <QQueue>
#include <QTimer>

#include "mongolib_global.h"
#include "filehansz.h"
#include "mongoconnection.h"
#include "mngserver.h"

#define CLIENT_VALID(cl) (cl&&cl->isWritable()&&cl->isReadable())

namespace Mongo {
class MongoConnection;
class MongoFileSocket;

class MONGOLIBSHARED_EXPORT MngThManager: public QObject{
    Q_OBJECT
public:
    MngThManager(const QString &stdDir = QDir::tempPath(), quint16 listenPort = 0,QObject *parent = nullptr);
    ~MngThManager();
    void createConnection(const QHostAddress &addr, quint16 port = 0);
    void closeConnection();

    bool sendInstruction(quint32 instr, quint32 toPrgm, const QByteArray &content = QByteArray(), quint32 args = 0);
    bool sendFile(QFile &file, quint64 type);
    bool sendHansz(SafeInstruction hansz);
public slots:
    void incomingConnection(MongoConnection *);
signals:
    void Message(SafeInstruction);
signals: // connection-based intern signals
    void connectionClosed();
    void connectionInitiated();
private:
    static QString standardDir;

    SafeInstruction lastingTransmission = nullptr;
    MongoConnection *client = nullptr;
    MngServer *server = nullptr;
    QThread *fileThread = nullptr;
    QQueue<SafeFileHansz> filequeue;
    MongoFileSocket *fileTransmission = nullptr;
    QTimer *timer = nullptr;

    bool serverActive = false;
    bool connectionVerified = false;
private slots:
    void incomingData(const SafeByteArray);
    void handleServerError(QAbstractSocket::SocketError);
    void handleClientError(QAbstractSocket::SocketError);
    void checkFileTransmissions();
    friend class MongoConnection;
public: //getter
    quint16 getPeerPort() const{return (CLIENT_VALID(client))?client->peerPort():0;}
    QHostAddress getPeerAddr() const{return (CLIENT_VALID(client))?client->peerAddress():QHostAddress(QHostAddress::Null);}
    quint16 getLocalPort()const{return (CLIENT_VALID(client))?client->localPort():0;}
    QHostAddress getLocalAddr()const{return (CLIENT_VALID(client))?client->localAddress():QHostAddress(QHostAddress::Null);}
    quint16 getServerPort()const;
    QHostAddress getServerAddr()const;
    bool isServerActive()const{return serverActive;}
    static QString getStandardDirectory(){return MngThManager::standardDir;}
};
}
#endif // MNGMANAGER_H
