#ifndef MNGMANAGER_H
#define MNGMANAGER_H

#include <QObject>
#include <QQueue>

#include "mongolib_global.h"
#include "mongoconnection.h"
#include "mngserver.h"

#define CLIENT_VALID(cl) (cl&&cl->isWritable()&&cl->isReadable())
class QTimer;
namespace Mongo {
class MongoConnection;

class MONGOLIBSHARED_EXPORT MngThManager: public QObject{
    Q_OBJECT
public:
    MngThManager(quint16 listenPort = 0,QObject *parent = nullptr);
    ~MngThManager();
    void createConnection(const QHostAddress &addr, quint16 port = 0);
    void closeConnection();

    void enqueueInstruction(SafeInstruction instr);
    void enqueueInstruction(quint32 instr, quint32 toPrgm, const QByteArray &content = QByteArray(), quint32 args = 0);
public slots:
    void incomingConnection(MongoConnection *);
signals:
    void Message(SafeInstruction);
signals: // connection-based intern signals
    void connectionClosed();
    void connectionInitiated();
private:
    QQueue<SafeInstruction> instructions;
    QTimer *timer = nullptr;
    SafeInstruction lastingTransmission = nullptr;
    MongoConnection *client = nullptr;
    MngServer *server = nullptr;
    QHostAddress address = QHostAddress(QHostAddress::Null);

    bool isSending = false;
    bool serverActive = false;
    bool connectionVerified = false;

    void sendInstruction(SafeInstruction hansz);
private slots:
    void updateManager();
    void incomingData(const SafeByteArray);
    void handleServerError(QAbstractSocket::SocketError);
    void handleClientError(QAbstractSocket::SocketError);
public: //getter
    quint16 getPeerPort() const{return (CLIENT_VALID(client))?client->peerPort():0;}
    QHostAddress getPeerAddr() const{return (CLIENT_VALID(client))?client->peerAddress():QHostAddress(QHostAddress::Null);}
    quint16 getLocalPort()const{return (CLIENT_VALID(client))?client->localPort():0;}
    QHostAddress getLocalAddr()const{return (CLIENT_VALID(client))?client->localAddress():QHostAddress(QHostAddress::Null);}
    quint16 getServerPort()const;
    QHostAddress getServerAddr()const;
    bool isServerActive()const{return serverActive;}
    friend class MongoConnection;
/*******************************************************************************
 * *****************************************************************************/

};
}
#endif // MNGMANAGER_H
