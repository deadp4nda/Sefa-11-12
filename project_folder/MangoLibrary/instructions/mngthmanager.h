#ifndef MNGMANAGER_H
#define MNGMANAGER_H

#include <QObject>
#include <QQueue>
#include <QtNetwork/QHostAddress>

#include "mangolib_global.h"
#include "mangoconnection.h"
#include "mngserver.h"

#define CLIENT_VALID(cl) (cl&&cl->isWritable()&&cl->isReadable())

class QTimer;
namespace Mango {
class MangoConnection;

class MngThManager: public QObject{
    Q_OBJECT
public:
    MngThManager(quint16 listenPort = 0,QObject *parent = nullptr);
    ~MngThManager();
    void createConnection(const QHostAddress &addr, quint16 port = 0);
    void closeConnection();

    void enqueueInstruction(SafeInstruction instr);
    void enqueueInstruction(quint32 instr, quint32 toPrgm, const QByteArray &content = QByteArray(), quint32 args = 0);
private slots:
    void incomingConnection(MangoConnection *);
signals:
    void Message(SafeInstruction);
signals: // connection-based intern signals
    void connectionClosed();
    void connectionInitiated();
    void connectionReceived();
private:
    QQueue<SafeInstruction> instructions;
    QTimer *timer = nullptr;
    SafeInstruction lastingTransmission = nullptr;
    MangoConnection *client = nullptr;
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
    friend class MangoConnection;
/*******************************************************************************
 * *****************************************************************************/

};
}
#endif // MNGMANAGER_H
