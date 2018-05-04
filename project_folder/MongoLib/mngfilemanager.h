#ifndef MNGFILEMANAGER_H
#define MNGFILEMANAGER_H

#include <QObject>
#include <QTimer>
#include <QQueue>
#include "mongolib_global.h"

namespace Mongo{
class MongoFileSocket;
class MngThManager;
class MngFileServer;

class MngFileManager : public QObject
{
    Q_OBJECT
public:
    explicit MngFileManager(MngThManager *parent = nullptr);
    int executing();
    void checkMate();
    void addFile(SafeFileHansz);
signals:
    void execNewFile(SafeFileHansz);
public slots:
    void setupServer(quint16 listeningPort);
    void receiveNewConnection(MongoFileSocket*);
private:
    SafeFileHansz executed = SafeFileHansz(nullptr);
    QQueue<SafeFileHansz> transmissions;
    MongoFileSocket *socket = nullptr;
    QTimer *timer = nullptr;
    QThread *transmissionThread = nullptr;
    MngFileServer *server = nullptr;
    MngThManager *parentMgr = nullptr;
};
}
#endif // MNGFILEMANAGER_H
