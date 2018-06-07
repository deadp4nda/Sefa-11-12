#ifndef MNGFILEMANAGER_H
#define MNGFILEMANAGER_H

#include <QObject>
#include <QQueue>
#include <QTimer>
#include <QFile>
#include <QDir>

#include "mongolib_global.h"

namespace Mongo{
class MngFileServer;
class MngFileSocket;
class MngFileManager: public QObject
{
    Q_OBJECT
public:
    explicit MngFileManager(const QDir& stdDir = QDir::tempPath()+"/pinkkarriertesclownsfischbatallion/",
                            quint16 port = 0,
                            QObject *parent = nullptr);
    void enqueueFile(SafeFileHansz);
    void enqueueFile(QFile *file,quint64);
private:
    QQueue<SafeFileHansz> files;
    QTimer *timer = nullptr;
    MngFileServer *server = nullptr;
    MngFileSocket *socket = nullptr;
    QDir saveDir = QDir::tempPath()+"/pinkkarriertesclownsfischbatallion/";
    quint16 port = 0;
    bool busy = false;
private slots:
    void updateManager();
    void sendFile(SafeFileHansz);
    void transmissionStarted(){busy=true;}
    void transmissionEnded(){busy=false;}
};
}
#endif // MNGFILEMANAGER_H
