#include "mngclient.h"
#include "mngmanager.h"
#include "mngserver.h"
#include <QByteArray>
#include <QFile>

namespace Mongo { // Client
MngClient::MngClient(const QHostAddress &toIp, quint16 port, MngManager *parent):
    QTcpSocket(parent),parentMgr(parent){
    connectToHost(toIp,port);
}
MngClient::MngClient(qintptr handle, MngManager *parent):
    QTcpSocket(parent),parentMgr(parent){
    setSocketDescriptor(handle);
}
void MngClient::handleReadyRead(){
    emit newMessage(readAll());
}
bool MngClient::sendWelcome(){
    QByteArray buffer;
    buffer.append((uchar)MONGO_TYPE_WELC);
    write(buffer);
    return true;
}
bool MngClient::sendClose(){
    QByteArray buffer;
    buffer.append((uchar)MONGO_TYPE_EXIT);
    return true;
}
bool MngClient::sendFile(QByteArray &buffer, QFile &file, uchar filetype){
    buffer.append(file.fileName());
    buffer.append(filetype);
    buffer.append(file.readAll());
    return write(buffer) == buffer.length();
}
bool MngClient::sendInstr(QByteArray &buffer, uchar instr, uint toPrgm, uchar args, QString toFile){
    buffer.append(instr);
    buffer.append((char*)&toPrgm,4);
    buffer.append(args);
    buffer.append(toFile);
    return write(buffer) == buffer.length();
}
}
