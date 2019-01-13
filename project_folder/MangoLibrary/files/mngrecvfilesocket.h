#ifndef MNGRECVFILESOCKET_H
#define MNGRECVFILESOCKET_H

#include "mangolib_global.h"

#include <QTcpSocket>
#include <QDir>

namespace Mango{
class MngRecvFileSocket : public QTcpSocket // Socket zum empfangen von Dateien
{
    Q_OBJECT
public:
    MngRecvFileSocket(qintptr descr,                //kriegt einen Socketdescriptor und ein standardverzeichnis und qt-magie
                      QString stdDir,
                      QObject *parent = nullptr);
    ~MngRecvFileSocket();                           // ein destruktor. wow. aufregend.
    SafeFileHansz getCurrent();
signals:
    void receivingStarted(SafeFileHansz);           // dateiempfang gestartet
    void receivingFinished();                       // -||- beendet
    void receivingCancelled();                      // -||- abgebrochen

    void justReceived(qint64);                      // daten, die gerade angekommen sind. für den fortschritt!
public slots:
    void handleReadyRead();                         // funktion, die bei bereitstehenden Daten aufgerufen wird.
private:
    SafeFileHansz current = nullptr;                // aktuelle datei. sogar im Smartpointer-mantel mit pistazienkröung. wow.
    QDir saveDir;                                   // standardverzeichnis.
    bool receivingSuccess = false;                  // na, wars erfolgreich?
};
}
#endif // MNGRECVFILESOCKET_H
