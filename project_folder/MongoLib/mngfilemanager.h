#ifndef MNGFILEMANAGER_H
#define MNGFILEMANAGER_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include <QQueue>
#include <QDir>
#include "mongolib_global.h"

namespace Mongo{
class MongoFileSocket;
class MngThManager;
class MngFileServer;

class MngFileManager : public QThread
{
    Q_OBJECT
public:
    explicit MngFileManager(QDir stdDir,MngThManager *parent = nullptr);
    ~MngFileManager();
    void run();
    void checkMate();
    void addFile(SafeFileHansz);
signals:
    void processNewFile(SafeFileHansz);
    void sendingFinished(SafeFileHansz);
    void newFileReceived(SafeFileHansz);
    void transmissionCancelled(SafeFileHansz);
public slots:
    void receiveNewConnection(MongoFileSocket*);
private:
    SafeFileHansz executed = SafeFileHansz(nullptr);
    QQueue<SafeFileHansz> transmissions;
    QQueue<MongoFileSocket*> pending;
    MongoFileSocket *inSocket = nullptr;
    MongoFileSocket *outSocket = nullptr;
    QTimer *timer = nullptr;
    MngThManager *parentMgr = nullptr;
    MngFileServer *server = nullptr;
    QDir &dir;
};
}
#endif // MNGFILEMANAGER_H
