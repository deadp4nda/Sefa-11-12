#ifndef MNGCLIENT_H
#define MNGCLIENT_H
#include <QTcpSocket>
#include <thread>
#include "mongolib.h"
namespace Mongo{
class MngClient: public QTcpSocket{
    Q_OBJECT
public:
    MngClient(const QHostAddress &toIp,quint16 port = 0, MngThManager *parent = nullptr);
    MngClient(qintptr handle,MngThManager *parent = nullptr);
signals:
    void newMessage(DataHansz*);
    void newFile(FileHansz*);
    void newInstruction(InstructionHansz*);
    void newUndefined(DataHansz*);
public slots:
    bool sendFile(FileHansz*);
    bool sendInstruction(InstructionHansz*);
    bool sendUndefined(DataHansz*);
private slots:
    void handleReadyRead();
private:
    quint64 stalledBytes = 0;
    FileHansz *lastFile;
    MngThManager *parentMgr;
    std::thread *sendingThread;
    bool stillSending = false;
private:
    void blobSending(FileHansz *);
};
}
#endif // MNGCLIENT_H
