#include "mngclient.h"
#include "mngthmanager.h"
#include "mngserver.h"
#include "datahansz.h"
#include <QByteArray>
#include <QDataStream>
#include <QCoreApplication>
#include <QFile>

namespace Mongo { // Client
MngClient::MngClient(const QHostAddress &toIp, quint16 port, MngThManager *parent):
    QTcpSocket(parent),parentMgr(parent){
    connectToHost(toIp,port);
    waitForConnected();
    connect(this, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));
}
MngClient::MngClient(qintptr handle, MngThManager *parent):
    QTcpSocket(parent),parentMgr(parent){
    setSocketDescriptor(handle);
    connect(this, SIGNAL(readyRead()),this,SLOT(handleReadyRead()));
}
void MngClient::processFile(QDataStream *stream){
    char firstBuffer[sizeof(File_header)];
    int writtenBytes = 0;
    writtenBytes = stream->readRawData(firstBuffer,sizeof(File_header));
    File_header *header = (File_header*)firstBuffer;
    char *buffer = new char[header->strLen];
    stream->readBytes(buffer, header->strLen);
    QFile file(parentMgr->getStandardDirectory()+QString(QByteArray(buffer,header->strLen)));
    FileHansz *hansz = new FileHansz(file,header->filetype);
    unsigned int byte = 1;
    char *buf = new char[byte];
    while(!atEnd()){
        stream->readBytes(buf,byte);
        file.write(buf,1);
    }
    delete []buffer;
    delete []buf;
    delete stream;
    emit newMessage(hansz);
}
void MngClient::handleReadyRead(){
    QDataStream *inStream = new QDataStream(this);
    char *initialBuf = new char[sizeof(Mongo_Hdr)];
    unsigned mngSize = (unsigned)sizeof(Mongo_Hdr);
    inStream->readBytes(initialBuf,mngSize);
    Mongo_Hdr *hdr = (Mongo_Hdr*)initialBuf;
    char *bytes;
    switch(hdr->mng_type){
    case MONGO_TYPE_FILE:
        processFile(inStream);
        break;
    case MONGO_TYPE_INST:
    {
        bytes = new char[sizeof(Instruction_header)];
        mngSize = (unsigned)sizeof(Instruction_header);
        inStream->readBytes(bytes,mngSize);
        Instruction_header *header = (Instruction_header*)(*bytes);
        char *content = new char[header->contLen];
        emit newMessage(new InstructionHansz(header->exCode,header->prgmSpec,header->args,new QByteArray(content,header->contLen)));
        delete[] content;
        delete[] bytes;
    }
        break;
    case MONGO_TYPE_EXIT:
        emit newMessage(new DataHansz(MONGO_TYPE_EXIT));
        break;
    case MONGO_TYPE_INIT:
        emit newMessage(new DataHansz(MONGO_TYPE_INIT));
        break;
    case MONGO_TYPE_UNSP:
    default:
        bytes = new char[MONGO_MAX_MEMSIZE];
        int i = 0;
        for(; i < MONGO_MAX_MEMSIZE&&!inStream->atEnd();i++){
            inStream->readRawData(bytes+i,1);
        }
        emit newMessage(new DataHansz(MONGO_TYPE_UNSP,new QByteArray(*bytes,i)));
    }
    delete inStream;
}
bool MngClient::sendSomething(DataHansz *data){
    QDataStream outStream(this);
    outStream << *data->getContentBuffer();
    uchar specifier = data->getSpec();
    FileHansz *f = (FileHansz*)data;
    InstructionHansz *i = (InstructionHansz*)data;
    switch(specifier){
    case MONGO_TYPE_FILE:
        delete f;
        break;
    case MONGO_TYPE_INST:
        delete i;
        break;
    case MONGO_TYPE_INIT:
    case MONGO_TYPE_EXIT:
    case MONGO_TYPE_UNSP:
    default:
        delete data;
    }
}
}
