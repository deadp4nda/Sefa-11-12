#include "mngclient.h"
#include "mngthmanager.h"
#include "mngserver.h"
#include "datahansz.h"
#include <exception>
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
    setReadBufferSize(MONGO_MAX_MEMSIZE);
}
MngClient::MngClient(qintptr handle, MngThManager *parent):
    QTcpSocket(parent),parentMgr(parent){
    setSocketDescriptor(handle);
    connect(this, SIGNAL(readyRead()),this,SLOT(handleReadyRead()));
    setReadBufferSize(MONGO_MAX_MEMSIZE);
}
void MngClient::handleReadyRead(){ //files will be sent seperately from their header
    if(stalledBytes){
        FileJumpLabel:
                waitForReadyRead();
        try{
            quint64 overallSize = 0;
            quint64 readSize = 0;
            quint64 written = 0;
            while(bytesAvailable()>0){
                char buffer[512];
                readSize = read(buffer,512);
                overallSize +=readSize;
                written = lastFile->writeBytes(buffer,readSize);
                if(readSize != written){
                    throw std::runtime_error("Data Under-/Overflow: "+std::to_string(readSize)+" Bytes received vs. "+
                                             std::to_string(written)+" Bytes Written @ Total Bytes received: "+std::to_string(overallSize));
                    break;
                }
                stalledBytes -= written;
            }
            if(stalledBytes == 0){
                emit newFile(lastFile);
            }
        }catch(std::runtime_error error){
            qDebug() << error.what();
            stalledBytes = 0;
            reset();
        }
        return;
    }

    //From here on it isn't a file's payload anymore
    quint64 available = 0;
    char *buffer = nullptr;
    try{
        available = bytesAvailable();
        if(available>MONGO_MAX_MEMSIZE){
            throw std::out_of_range("available bytes out of valid range: " + std::to_string(available) + " Bytes available");
        }
        char alloc[available];
        buffer = alloc;
        quint64 r = read(buffer,available);
        if(r != available){
            throw std::runtime_error("Data Under-/Overflow: "+std::to_string(r)
                                     +" Bytes read vs. "+std::to_string(available)+
                                     " Bytes available");
        }
    }catch(std::runtime_error error){
        qDebug() << error.what();
        reset();
        stalledBytes = 0;
        return;
    }catch(std::out_of_range error){
        qDebug() << error.what();
        reset();
        stalledBytes = 0;
        return;
    }
    try{
        Mongo_header *typeHeader = (Mongo_header*)buffer;
        if(typeHeader->mng_type == MONGO_TYPE_INIT){
            DataHansz *hansz = new DataHansz(MONGO_TYPE_INIT,new QByteArray(buffer,available));
            emit newMessage(hansz);
            return;
        }else if(typeHeader->mng_type == MONGO_TYPE_INST){
            InstructionHansz *hansz = new InstructionHansz(new QByteArray(buffer,available));
            emit newInstruction(hansz);
            return;
        }else if(typeHeader->mng_type == MONGO_TYPE_FILE){
            File_header *header = (File_header*)(buffer+sizeof(Mongo_header));
            stalledBytes = header->fileLen;
            lastFile = new FileHansz(new QByteArray(buffer,sizeof(Mongo_header)+sizeof(File_header)+header->strLen));
            goto FileJumpLabel;
        }else if(typeHeader->mng_type == MONGO_TYPE_UNSP){
            DataHansz *hansz = new DataHansz(new QByteArray(buffer,available));
            emit newUndefined(hansz);
            return;
        }else if(typeHeader->mng_type == MONGO_TYPE_EXIT){
            DataHansz *hansz = new DataHansz(MONGO_TYPE_EXIT,new QByteArray(buffer,available));
            emit newMessage(hansz);
            parentMgr->closeConnection();
            return;
        }else{
            throw std::runtime_error("THE FUCK JUST HAPPENED?!?!?!");
        }
    }catch(std::exception exc){
        qDebug() << exc.what();
    }
}
bool MngClient::sendFile(FileHansz *hansz){
    stillSending = true;
    try{
        quint64 written = write(*hansz->getWholeBuffer());
        if(written != hansz->getWholeBuffer()->size()){
            throw std::runtime_error("Data Under-/Overflow: "+std::to_string(written)
                                     +" Bytes written vs. "+std::to_string(hansz->getWholeBuffer()->size())+
                                     " Bytes to write");
        }
    }catch(std::runtime_error err){
        qDebug() << err.what();
    }
    //blobSending(hansz)
    return false;
}
bool MngClient::sendInstruction(InstructionHansz *instruction){
    try{
        quint64 written = write(*instruction->getWholeBuffer());
        if(written != instruction->getWholeBuffer()->size()){
            throw std::runtime_error("Data Under-/Overflow: "+std::to_string(written)
                                     +" Bytes written vs. "+std::to_string(instruction->getWholeBuffer()->size())+
                                     " Bytes to write");
        }
        return true;
    }catch(std::runtime_error err){
        qDebug() << err.what();
        return false;
    }
}
bool MngClient::sendUndefined(DataHansz *hansz){
    try{
        quint64 written = write(*hansz->getWholeBuffer());
        if(written != hansz->getWholeBuffer()->size()){
            throw std::runtime_error("Data Under-/Overflow: "+std::to_string(written)
                                     +" Bytes written vs. "+std::to_string(hansz->getWholeBuffer()->size())+
                                     " Bytes to write");
        }
        return true;
    }catch(std::runtime_error err){
        qDebug() << err.what();
        return false;
    }
}
}
