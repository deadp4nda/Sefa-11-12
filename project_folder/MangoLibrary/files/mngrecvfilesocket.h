#ifndef MNGRECVFILESOCKET_H
#define MNGRECVFILESOCKET_H

#include "mangolib_global.h"

#include <QTcpSocket>
#include <QDir>

namespace Mango{
class MngRecvFileSocket : public QTcpSocket
{
    Q_OBJECT
public:
    MngRecvFileSocket(qintptr descr,
                      QString stdDir,
                      QObject *parent = nullptr);
    ~MngRecvFileSocket();
    SafeFileHansz getCurrent();
signals:
    void receivingStarted(SafeFileHansz);
    void receivingFinished();
    void receivingCancelled();

    void justReceived(qint64);
public slots:
    void handleReadyRead();
private:
    SafeFileHansz current = nullptr;
    QDir saveDir;
    bool receivingSuccess = false;
};
}
#endif // MNGRECVFILESOCKET_H