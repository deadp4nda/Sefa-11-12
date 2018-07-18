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
                  QString stdDir,
                  QObject *parent = nullptr);
    MngFileSocket(qintptr descr,
                  QString stdDir,
                  QObject *parent = nullptr);
    ~MngFileSocket();
    void send(SafeFileHansz);
    void finish();
    SafeFileHansz getReceiving(){return receiving;}
    SafeFileHansz getSending(){return current;}
signals:
    void startedTransmission(SafeFileHansz);
    void endedTransmission(SafeFileHansz);
    void transmissionCancelled(SafeFileHansz);
    void startedReceiving(SafeFileHansz);
    void finishedReceiving(SafeFileHansz);
public slots:
    void handleReadyRead();
private:
    SafeFileHansz current = nullptr;
    SafeFileHansz receiving = nullptr;
    QHostAddress addr;
    quint16 port;
    QDir stdDirectory;
private slots:
    friend class FileHansz;
};
}
#endif // MNGFILESOCKET_H
