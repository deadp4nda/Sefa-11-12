#include "mngfilesocket.h"
#include "files/filehansz.h"
#include <iostream>

//extern "C"{
//void ChryHexdump(const char *data_buffer, const unsigned int length, FILE *output = stdout){
//    fprintf(output,"\nNEW DUMP:\n");
//    unsigned char byte;
//    unsigned int i, j;
//    for (i=0;i < length; i++){
//        byte = data_buffer[i];
//        fprintf(output,"%02x ",byte);
//        if((i%16)==15||(i==length-1)){
//            for(j=0;j<15-(i%16);j++) fprintf(output,"    ");
//            fprintf(output,"| ");
//            for(j=(i-(i%16));j<=i;j++){
//                byte = data_buffer[j];
//                if((byte>31)&& (byte <127)) fprintf(output,"%c",byte);
//                else fprintf(output,".");
//            }
//            fprintf(output,"\n");
//        }
//    }
//}
//}

namespace Mongo{
MngFileSocket::MngFileSocket(qintptr descr, QString stdDir, QObject *parent):
    QTcpSocket(parent),stdDirectory(stdDir){
    setSocketDescriptor(descr);
    connect(this,&MngFileSocket::readyRead,this,&MngFileSocket::handleReadyRead);
}
MngFileSocket::MngFileSocket(const QHostAddress &address, quint16 port,
                             QString stdDir, QObject *parent):
    QTcpSocket(parent),addr(address),port(port),stdDirectory(stdDir){
    connectToHost(address,port);
    waitForConnected();
    connect(this,&MngFileSocket::readyRead,this,&MngFileSocket::handleReadyRead);
}
void MngFileSocket::handleReadyRead(){
    if(!receiving) {
        receiving = SafeFileHansz(new FileHansz(stdDirectory,this));
        emit startedReceiving(receiving);
    }
    receiving->addData( read(bytesAvailable()) );
}
void MngFileSocket::fileComplete(){
    emit finishedReceiving(receiving);
    receiving = nullptr;
}
QString operator*(const QString & str,qint32 times){
    QString retVal;
    for(int i = 0;i < times; i++){
        retVal+=str;
    }
    return retVal;
}
void MngFileSocket::send(SafeFileHansz hansz){
    emit startedTransmission();
    current = hansz;

    QByteArray test = hansz->getHeaders();
    ChryHexdump(test,test.size(),"MngFileSocket::send",stderr);

    write(test);
    waitForBytesWritten(INT_MAX);

    QFile* file = hansz->getFile();
    while(!file->atEnd()){
//        qDebug() << "writing: " << write(file->read(FILE_READ_MAXLENGTH)) << " Bytes";
//        waitForBytesWritten();
    }

    current = nullptr;
    emit endedTransmission();
}
MngFileSocket::~MngFileSocket(){
    if(current)
        emit transmissionCancelled(current);
    if(receiving)
        emit transmissionCancelled(receiving);
    disconnectFromHost();
    waitForDisconnected();
    close();
}
}
