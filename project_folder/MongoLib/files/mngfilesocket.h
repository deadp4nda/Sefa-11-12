#ifndef MNGFILESOCKET_H
#define MNGFILESOCKET_H

#include "mongolib_global.h"

#include <QTcpSocket>

namespace Mongo{
class MngFileSocket : public QTcpSocket
{
    Q_OBJECT
public:
    MngFileSocket(const QHostAddress &address,
                  quint16 port,
                  QObject *parent = nullptr);
    MngFileSocket(qintptr descr,QObject *parent = nullptr);
    ~MngFileSocket();
    void send(SafeFileHansz);
signals:
    void startedTransmission();
    void endedTransmission();
    void transmissionCancelled(SafeFileHansz);
public slots:
    void handleReadyRead();
private:
    SafeFileHansz current;
    QHostAddress addr;
    quint16 port;
};
}
#endif // MNGFILESOCKET_H
