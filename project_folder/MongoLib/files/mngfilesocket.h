#ifndef MNGFILESOCKET_H
#define MNGFILESOCKET_H

#include "mongolib_global.h"

#include <QTcpSocket>
#include <QDir>

namespace Mongo{
class MngFileSocket : public QTcpSocket
{
    Q_OBJECT
public:
    MngFileSocket(const QHostAddress &address,
                  quint16 port,
                  QString stdDir = QDir::tempPath()+"/pinkkarriertesclownsfischbatallion/",
                  QObject *parent = nullptr);
    MngFileSocket(qintptr descr,
                  QString stdDir = QDir::tempPath()+"/pinkkarriertesclownsfischbatallion/",
                  QObject *parent = nullptr);
    ~MngFileSocket();
    void send(SafeFileHansz);
signals:
    void startedTransmission();
    void endedTransmission();
    void transmissionCancelled(SafeFileHansz);
    void startedReceiving(SafeFileHansz);
    void finishedReceiving(SafeFileHansz);
public slots:
    void handleReadyRead();
private:
    SafeFileHansz current;
    SafeFileHansz receiving;
    QHostAddress addr;
    quint16 port;
    QDir stdDirectory;
};
}
#endif // MNGFILESOCKET_H
