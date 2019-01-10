#include "mangoconnection.h"
#include <QDataStream>
#include "../instructions/mngthmanager.h"
#include <iostream>

namespace Mango{
MangoConnection::MangoConnection(const QHostAddress &toIp, quint16 port, MngThManager *parent):
    QSslSocket(parent),foreignHost(toIp),atPort(port),parentManager(parent){
    connectToHostEncrypted(foreignHost.toString(),port,QIODevice::ReadWrite,foreignHost.protocol());
    waitForEncrypted();
    connect(this,SIGNAL(readyRead()),this,SLOT(handleReadyRead()));
    stream.setDevice(this);
}

MangoConnection::MangoConnection(qintptr handle, MngThManager *parent):
    QSslSocket(parent),parentManager(parent){
    setSocketDescriptor(handle);
    connect(this, SIGNAL(readyRead()),this,SLOT(handleReadyRead()));
    stream.setDevice(this);
}

void MangoConnection::handleReadyRead(){
    SafeByteArray array(new QByteArray);
    qint64 available = bytesAvailable();
//    std::cerr << available << "\n";
    quint8 byte;
    for(int i = 0; i < available; i++){
        stream >> byte;
        array->append(byte);
    }
    parentManager->incomingData(array);

}

bool MangoConnection::send(const SafeByteArray array){
    return stream.writeRawData(array->constData(),array->length()) == array->size();
}

}
