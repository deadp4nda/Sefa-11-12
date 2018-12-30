#ifndef MNGSENDFILESOCKET_H
#define MNGSENDFILESOCKET_H

#include "mangolib_global.h"


#include <QTcpSocket>
#include <QDir>

class QTimer;

namespace Mango{
class MngSendFileSocket : public QTcpSocket
{
    Q_OBJECT
public:
    MngSendFileSocket(const QHostAddress &address,
                      quint16 port,
                      QString stdDir,
                      QObject *parent = nullptr);
    ~MngSendFileSocket();
    void send(SafeFileHansz);
    SafeFileHansz getCurrent();
signals:
    void transmissionStarted(SafeFileHansz);
    void transmissionComplete();
    void transmissionCancelled();

    void justWritten(qint64);

    void startNextShot();
public slots:
    void handleFinishReadyRead();
private:
    QTimer *timer = nullptr;
    SafeFileHansz current = nullptr;
    QFile *file = nullptr;
    QHostAddress addr = QHostAddress::Null;
    quint16 sendingPort = 0;
    QDir saveDir;
    bool transmissionSuccess = false;
private slots:
    void sendNextPortion();
    void prepareNextShot();
};
}
#endif // MNGSENDFILESOCKET_H
