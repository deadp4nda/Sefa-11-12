#ifndef MNGFILEMANAGER_H
#define MNGFILEMANAGER_H

#include <QObject>
#include <QQueue>
#include <QTimer>
#include <QThread>
#include <QFile>
#include <QDir>

#include "mangolib_global.h"

#define STD_TEMP_DIR "/pinkkarriertesclownsfischbatallion/"

namespace Mango{
class MngFileServer;
class MngSendFileSocket;
class MngRecvFileSocket;
class FileHansz;

class MngFileManager: public QObject    // Managerklasse zum verschicken von Dateien
{
    Q_OBJECT
public:
    enum MangolibError{ // ein paar ausgewählte, wunderbare Errors
        StillFilesToSend,
        NoConnectionToClose,
        StillConnected,
        ConnectionFailed,
        NoRemoteConnectionToClose,
        NoConnectionReceivable,
        FileInvalid
    };
public:
    MngFileManager(quint16 port = 0,                                            // konstruktor, nimmt port, standardpfad
                            QDir stdDir = QDir(QDir::tempPath()+STD_TEMP_DIR),
                            QObject *parent = nullptr);
    ~MngFileManager();                                                  // destruktor
    void lockServer();
    void setConnectionProperties(QHostAddress foreignHost, quint16 port);                           // verbindung setzen, zu der Dateien verschickt werden
    void forceNewConnection(QHostAddress foreignHost, quint16 port);                                //erzwingt neue verbindung, löscht dateien in queue
    QString getConnCredentials(){return foreignHost.toString()+" "+QString::number(foreignPort);}   //debug funktion
public slots:
    void activate();                                //aktiviert dateiserver. ohne die fliegt alles in die luft
    void enqueueFile(SafeFileHansz hansz);          // datei in warteschlange zum versenden packen
    void enqueueFile(QFile *file,quint64 type);     // ^
    void closeOutgoingConnection();                 // was soll ich dazu noch sagen?
    void closeIncomingConnection();                 // ^
signals:
    void fileReceivingStarted(SafeFileHansz);       // signale. werden später abgefangen und an lua weitergeschickt
    void fileSuccessfulReceived();
    void fileTransmissionStarted(SafeFileHansz);
    void fileTransmissionEnded();

    void fileCancelled();

    void connectionClosed();
    void connectionInitiated();
    void remoteConnectionReceived();
    void remoteConnectionClosed();

    void error(MangolibError);
    void justSent(qint64);
    void justReceived(qint64);
    void noFilesToSend();
private:
    QQueue<SafeFileHansz> files;        //datei-warteschlange

    QTimer *timer = nullptr;
    MngFileServer *server = nullptr;                // nimmt verbindungen entgegen
    MngSendFileSocket *sendingSocket = nullptr;     // socket für Dateisenden
//    QThread *sendingThread = nullptr;
    MngRecvFileSocket *receivingSocket = nullptr;   // -||-       Dateiempfangen
//    QThread *receivingThread = nullptr;

    QDir saveDir = QDir::tempPath()+STD_TEMP_DIR;   // speicherpfad
    bool serverActive = false;                      //blah, irgendwas, was ich vor gefühlten 500000 Jahren mal gebraucht hab, selbsterklärend
    QHostAddress foreignHost = QHostAddress::Null;  // anderer Computer
    quint16 foreignPort = 0;
    quint16 serverPort = 0;

    int createConnection(const QHostAddress & addr, quint16 port); // verbindung aufbauen

private slots:
    void updateManager();                                                       // wird regelmäßig aufgerufen, checkt ob die queue leer ist
    void incomingConnection(MngRecvFileSocket*);                                // verbindung kommt rein
    void handleServerError(QAbstractSocket::SocketError errorCode);             // behandeln von fehlersen. die böhhhsen fehlerse
    void handleSendingClientError(QAbstractSocket::SocketError errorCode);
    void handleReceivingClientError(QAbstractSocket::SocketError errorCode);    // bis hier. meine fehlerse.

    void initializeSendingSocket();     // initialisieren/ aufräumen der sockets
    void initializeReceivingSocket();
    void cleanupSendingSocket();
    void cleanupReceivingSocket();
};
}
#endif // MNGFILEMANAGER_H
