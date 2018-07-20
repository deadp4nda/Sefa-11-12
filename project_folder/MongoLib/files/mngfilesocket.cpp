#include "mngfilesocket.h"
#include "files/filehansz.h"
#include <iostream>

namespace Mongo{
MngFileSocket::MngFileSocket(qintptr descr, QString stdDir, QObject *parent):
    QTcpSocket(parent),stdDirectory(stdDir){
    setSocketDescriptor(descr);
    connect(this,&MngFileSocket::readyRead,
            this,&MngFileSocket::handleReadyRead);
}

MngFileSocket::MngFileSocket(const QHostAddress &address, quint16 port,
                             QString stdDir, QObject *parent):
    QTcpSocket(parent),addr(address),port(port),stdDirectory(stdDir){
    connectToHost(address,port);
    waitForConnected();
    connect(this,&MngFileSocket::readyRead,
            this,&MngFileSocket::handleReadyRead);
}

void MngFileSocket::handleReadyRead(){
    QByteArray bufferOfReceived = read(bytesAvailable());
    qDebug() << "Received " << bufferOfReceived.length() << " Bytes";
    if(!receiving) {
        receiving = SafeFileHansz(new FileHansz(stdDirectory,this));
        receiving->addData( bufferOfReceived);
        emit startedReceiving(receiving);
    }
    receiving->addData(bufferOfReceived);
}

void MngFileSocket::send(SafeFileHansz hansz){
    emit startedTransmission(hansz);
    current = hansz;

    QByteArray test = current->getHeaders();
    ChryHexdump(test,test.size(),"MngFileSocket::send",stderr);

    qDebug() << "writing: " << write(test) << " Bytes";
    waitForBytesWritten(INT_MAX);

    QFile* file = current->getFile();
    while(!file->atEnd()){
        test = file->read(FILE_READ_MAXLENGTH);
        qDebug() << "writing: " << write(test) << " Bytes";
    }
    current = nullptr;
    emit endedTransmission(hansz);
}

void MngFileSocket::finish(){
    if(receiving){
        receiving->finishFile();
        emit finishedReceiving(receiving);
        receiving = nullptr;
    }
}

MngFileSocket::~MngFileSocket(){
    if(current){
        disconnectFromHost();
        waitForDisconnected();
        emit transmissionCancelled(current);
    }
    if(receiving){
        finish();
        emit transmissionCancelled(receiving);
    }
    close();
}
}
