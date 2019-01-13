#ifndef MNGMANAGER_H
#define MNGMANAGER_H

#include <QObject>
#include <QQueue>
#include <QtNetwork/QHostAddress>

#include "mangolib_global.h"
#include "mangoconnection.h"
#include "mngserver.h"

#define CLIENT_VALID(cl) (cl&&cl->isWritable()&&cl->isReadable()) // MAkro, das testet, ob Socket gültig ist

class QTimer;
namespace Mango {
class MangoConnection;

class MngThManager: public QObject{ // anweisungsmanager für anweisungen, die anweisen
    Q_OBJECT
public:
    MngThManager(quint16 listenPort = 0,QObject *parent = nullptr); // konstruktor, kriegt port, auf dem der Server auf Verbindung hören soll
    ~MngThManager();                                                // destruktor
    int createConnection(const QHostAddress &addr, quint16 port = 0);// verbindung herstellen zu xyz auf port zyx
    void closeConnection();                                             // verbindung beenden

    void enqueueInstruction(SafeInstruction instr);                 // anweisung in warteschlange zum versenden stellen
    void enqueueInstruction(quint32 instr, quint32 toPrgm, const QByteArray &content = QByteArray(), quint32 args = 0); // siehe eine zeile drüber
private slots:
    void incomingConnection(MangoConnection *); // wird aufgerufen, wenn eine neue "MangoConnection" bereitsteht
signals:
    void Message(SafeInstruction);              // eine neue Anweisung ist hereingekommen
signals: // connection-based intern signals
    void connectionClosed();            // verbindung beendet
    void connectionInitiated();         // verbindung erstellt
    void connectionReceived(QHostAddress);// verbindung erhalten von xyz. die adresse wird im dateimanager gebraucht.
private:
    QQueue<SafeInstruction> instructions; // warteschlange mit anweisungen
    QTimer *timer = nullptr;                // timer für die abfrage der warteschlange
    SafeInstruction lastingTransmission = nullptr;// im moment verschickte anweisung
    MangoConnection *client = nullptr;          // aktuelle Verbindung, repräsentiert als socket
    MngServer *server = nullptr;                // serverklasse für neue verbindungen
    QHostAddress address = QHostAddress(QHostAddress::Null); // anderer computer

    bool isSending = false;         // ein haufen Flags
    bool serverActive = false;
    bool connectionVerified = false;

    void sendInstruction(SafeInstruction hansz); // funktion zum direkten versenden einer datei. wird nur intern aufgerufen
    void closeConnectionPrivate(); //tatsächliches schließen der Verbindung. das andere setzt nur ein flag dafür.
    bool connectionClosing = false; // ein flag. ist die Verbindung gerade im Prozess des schließens?
private slots:
    void updateManager(); // prüffunktion für die Warteschlange
    void incomingData(const SafeByteArray); // eingehende Daten, wird vom socket aus aufgerufen, macht matsch zu sinnvollen Daten
    void handleServerError(QAbstractSocket::SocketError);       // fehlerbehandlung
    void handleClientError(QAbstractSocket::SocketError);
public:                                                         //getter
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
