#ifndef MNGFILEMANAGER_H
#define MNGFILEMANAGER_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include <QQueue>
#include "mongolib_global.h"

namespace Mongo{
class MongoFileSocket;
class MngThManager;
class MngFileServer;

class MngFileManager : public QThread
{
    Q_OBJECT
public:
    explicit MngFileManager(MngThManager *parent = nullptr);
    void run();
    void checkMate();
    void addFile(SafeFileHansz);
signals:
    void execNewFile(SafeFileHansz);
    void sendingFinished(SafeFileHansz);
    void newFileReceived(SafeFileHansz);
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
};
}
#endif // MNGFILEMANAGER_H
