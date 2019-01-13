#ifndef MNGSENDFILESOCKET_H
#define MNGSENDFILESOCKET_H

#include "mangolib_global.h"


#include <QTcpSocket>
#include <QDir>

class QTimer;

namespace Mango{
class MngSendFileSocket : public QTcpSocket // socket zum senden von Dateien
{
    Q_OBJECT
public:
    MngSendFileSocket(const QHostAddress &address,          //kriegt zieladresse, port und standardverzeichnis
                      quint16 port,
                      QString stdDir,
                      QObject *parent = nullptr);
    ~MngSendFileSocket();                               // destruktor
    void send(SafeFileHansz);                           // funktion, die Dateien versendet. also in das groooße internetz schickt.
    SafeFileHansz getCurrent();
signals:
    void transmissionStarted(SafeFileHansz); // übertragung gestartet von der Datei, die durch den SafeFileHansz bezeichnet wird.
    void transmissionComplete();             // -||- beendet
    void transmissionCancelled();            // -||- abgebrochen

    void justWritten(qint64);                   // für den FORTSCHRITT!!!

    void startNextShot();                       // implementierungsdetail, also unwichtig
public slots:
    void handleFinishReadyRead();               // funktion, die aufgerufen wird, wenn die Abschlussbytesequenz gesendet wird oder der header zurück
private:
    QTimer *timer = nullptr;                    // implementierungsdetail
    SafeFileHansz current = nullptr;            // datei im praktischen Smartpointermantel
    QFile *file = nullptr;                      // dateiobjekt-pointer
    QHostAddress addr = QHostAddress::Null;     // adresse des gegenübers
    quint16 sendingPort = 0;                    // port
    QDir saveDir;                               // standardverzeichnis
    bool transmissionSuccess = false;           // na, wars erfolgreich?
private slots:
    void sendPayload();                         // die Datei in kleinen stückchen ohne header verschicken. der war schon.
};
}
#endif // MNGSENDFILESOCKET_H
