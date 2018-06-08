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
    void send(SafeFileHansz);
signals:
    void startedTransmission();
    void endedTransmission();
public slots:
    void handleReadyRead();
private:
    quint16 port;
    QHostAddress addr;
};
}
#endif // MNGFILESOCKET_H
