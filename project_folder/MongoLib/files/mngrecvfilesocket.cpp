#include "mngrecvfilesocket.h"
#include "filehansz.h"
namespace Mongo {
MngRecvFileSocket::MngRecvFileSocket(qintptr descr,
                                     QString stdDir,
                                     QObject *parent):QTcpSocket (parent),saveDir(stdDir){
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
        this->write(endingOrder());
        waitForBytesWritten();
        emit receivingFinished();
    }
}
MngRecvFileSocket::~MngRecvFileSocket(){
    if(state() == QTcpSocket::ConnectedState){
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
