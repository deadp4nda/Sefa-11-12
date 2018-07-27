#ifndef MNGSENDFILESOCKET_H
#define MNGSENDFILESOCKET_H

#include "mongolib_global.h"


#include <QTcpSocket>
#include <QDir>

namespace Mongo{
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

    void transmitFile();
    void justWritten(qint64);
public slots:
    void handleFinishReadyRead();
private:
    SafeFileHansz current = nullptr;
    QHostAddress addr = QHostAddress::Null;
    quint16 sendingPort = 0;
    QDir saveDir;
    bool transmissionSuccess = false;
private slots:
    void sendFile();
};
}
#endif // MNGSENDFILESOCKET_H
