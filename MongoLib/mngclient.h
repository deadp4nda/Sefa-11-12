#ifndef MNGCLIENT_H
#define MNGCLIENT_H
#include <QTcpSocket>
#include "mongolib.h"
namespace Mongo{
class MngClient: public QTcpSocket{
    Q_OBJECT
public:
    MngClient(const QHostAddress &toIp,quint16 port = 0, MngManager *parent = nullptr);
    MngClient(qintptr handle,MngManager *parent = nullptr);
    bool sendWelcome();
    bool sendClose();
    bool sendInstr(QByteArray &buffer, uchar instr,uint toPrgm,uchar args,QString toFile);
    bool sendFile(QByteArray &buffer, QFile &file,uchar filetype);
signals:
    void newMessage(QByteArray);
private slots:
    void handleReadyRead();
private:
    MngManager *parentMgr;
    bool continuity;
};
}
#endif // MNGCLIENT_H
