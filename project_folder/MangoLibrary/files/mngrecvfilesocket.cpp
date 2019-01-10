#include "mngrecvfilesocket.h"
#include "filehansz.h"
namespace Mango {
MngRecvFileSocket::MngRecvFileSocket(qintptr descr,
                                     QString stdDir,
                                     QObject *parent):QSslSocket(parent), saveDir(stdDir){
    setSocketDescriptor(descr);
    connect(this, &MngRecvFileSocket::readyRead,
            this, &MngRecvFileSocket::handleReadyRead);
}
SafeFileHansz MngRecvFileSocket::getCurrent(){
    return current;
}
void MngRecvFileSocket::handleReadyRead(){
    QByteArray bufferOfReceived = read(bytesAvailable());
    emit justReceived(bufferOfReceived.size());
//    qDebug() << "Received " << bufferOfReceived.length() << " Bytes";
    if(!current){
        current = SafeFileHansz(new FileHansz(saveDir));
        current->addData(bufferOfReceived);
        write(bufferOfReceived);
        //ChryHexdump(bufferOfReceived.data(),bufferOfReceived.length(),"MngRecvSocket::handleReadyRead",stdout);
        flush();
        emit receivingStarted(current);
        return;
    }
    bool finished = false;
    if(current->getFileSize() == current->getFile()->size()+bufferOfReceived.length()){ // file completely transferred
        finished = true;
        receivingSuccess = true;
    }
    current->addData(bufferOfReceived, finished);
    if(finished){
        current->getFile()->close();
        this->write(endingOrder());
        waitForBytesWritten();
        emit receivingFinished();
    }
}
MngRecvFileSocket::~MngRecvFileSocket(){
    if(state() == QSslSocket::ConnectedState){
        disconnectFromHost();
        waitForDisconnected(INT_MAX);
    }
    disconnect(this, &MngRecvFileSocket::readyRead,
            this, &MngRecvFileSocket::handleReadyRead);
    if(!receivingSuccess){
        emit receivingCancelled();
    }
}
}
