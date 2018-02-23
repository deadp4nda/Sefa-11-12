#ifndef MNGCLIENT_H
#define MNGCLIENT_H
#include <QTcpSocket>
#include "mongolib.h"
namespace Mongo{
class MngClient: public QTcpSocket{
    Q_OBJECT
public:
    MngClient(const QHostAddress &toIp,quint16 port = 0, MngThManager *parent = nullptr);
    MngClient(qintptr handle,MngThManager *parent = nullptr);
signals:
    void newMessage(DataHansz*);
    void newFile(const FileHansz*);
    void newInstruction(const InstructionHansz*);
    void newUndefined(const DataHansz*);
private slots:
    void handleReadyRead();
    void sendFile(FileHansz*);
    void sendInstruction(InstructionHansz*);
    void sendUndefined(DataHansz*);
private:
    MngThManager *parentMgr;
};
}
#endif // MNGCLIENT_H
