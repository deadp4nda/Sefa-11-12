#include "datahansz.h"
#include "mngthmanager.h"

namespace Mongo{
DataHansz::DataHansz(QByteArray *arrayPtr){  //correct DataOrder, cant be nullptr
    if(!arrayPtr){
        spec = MONGO_TYPE_INVA;
        typeString = "IV:N"; //invalid nullpointer
        return;
    }
    if(arrayPtr->size() > MONGO_MAX_MEMSIZE){
        spec = MONGO_TYPE_INVA;
        typeString = "IV:S"; //invalid, size overflow
        delete arrayPtr;
        return;
    }
    arr = arrayPtr;
    Mongo_header *header = (Mongo_header*)arrayPtr->data();
    spec = header->mng_type;
    switch(spec){
    case MONGO_TYPE_EXIT:
        typeString = "EXIT";
        break;
    case MONGO_TYPE_FILE:
        typeString = "FILE";
        break;
    case MONGO_TYPE_INIT:
        typeString = "INIT";
        break;
    case MONGO_TYPE_INST:
        typeString = "INST";
        break;
    case MONGO_TYPE_UNSP:
    default:
        typeString = "UNSP";
        break;
    }
}
DataHansz::DataHansz(quint8 type, QByteArray *buf){ //just payload and type
    if(buf){
        if(buf->size()>(MONGO_MAX_MEMSIZE-sizeof(type))){
            spec = MONGO_TYPE_INVA;
            typeString = "IV:S"; //invalid, size overflow
            delete buf;
            return;
        }
    }
    spec = type;
    switch(spec){
    case MONGO_TYPE_EXIT:
        typeString = "EXIT";
        break;
    case MONGO_TYPE_FILE:
        typeString = "FILE";
        break;
    case MONGO_TYPE_INIT:
        typeString = "INIT";
        break;
    case MONGO_TYPE_INST:
        typeString = "INST";
        break;
    case MONGO_TYPE_UNSP:
    default:
        typeString = "UNSP";
        break;
    }
    arr = buf;
    if(buf)delete buf;
}
DataHansz::~DataHansz(){
    if(arr)
        delete arr;
}
InstructionHansz::InstructionHansz(QByteArray *buf):DataHansz(buf){
    if(spec == MONGO_TYPE_INVA){
        return;
    }
    Instruction_header *header = (Instruction_header*)(buf->data()+sizeof(Mongo_header));
    exCode = header->exCode;
    toProgram = header->prgmSpec;
    args = header->args;
    if(buf->size() != header->contLen){
        qDebug() << "[WARNING] real buffer size not equal to expected size";
    }
}
InstructionHansz::InstructionHansz(quint8 exCode, quint32 prgmCode, quint8 args, QByteArray *buf):
    DataHansz(MONGO_TYPE_INST,buf),exCode(exCode),toProgram(prgmCode),args(args){
    if(spec == MONGO_TYPE_INVA){
        return;
    }
    char buffer[sizeof(Mongo_header)+sizeof(Instruction_header)+buf->size()];
    Instruction_header h;
    h.args =args;
    h.contLen = buf?buf->size():0;
    h.exCode = exCode;
    h.prgmSpec = prgmCode;
//    buffer = (char*)&h;
    memcpy(buffer,(char*)&spec,sizeof(spec));
    memcpy(buffer+sizeof(spec),&h,sizeof(Instruction_header));
    memcpy(buffer,arr->data(),arr->size());
    arr->clear();
    delete arr;
    arr = new QByteArray(buffer,sizeof(Mongo_header)+sizeof(Instruction_header)+buf->size());
}
FileHansz::FileHansz(QFile &inFile, quint8 type):
    DataHansz(MONGO_TYPE_FILE,nullptr),file(inFile.fileName()),filetype(type){
    if(spec == MONGO_TYPE_INVA){
        return;
    }
    for(int i = file.fileName().size()-1;i >= 0 ;i--){
        if(file.fileName()[i]=='\\' || file.fileName()[i]=='/'){
            break;
        }
        filename.prepend(file.fileName()[i]);
    }
}
FileHansz::FileHansz(QString fileName, quint8 type):
    DataHansz(MONGO_TYPE_FILE,nullptr),file(fileName),filetype(type){
    if(spec == MONGO_TYPE_INVA){
        return;
    }
    for(int i = file.fileName().size()-1;i >= 0 ;i--){
        if(file.fileName()[i]=='\\' || file.fileName()[i]=='/'){
            break;
        }
        filename.prepend(file.fileName()[i]);
    }
}
FileHansz::FileHansz(QByteArray *arrPtr):DataHansz(arrPtr){
    if(spec == MONGO_TYPE_INVA){
        return;
    }
    File_header *header = (File_header*)arrPtr->data()+sizeof(Mongo_header);
    QString filename = Mongo::MngThManager::getStandardDirectory()+QString(QByteArray((char*)(header+sizeof(File_header)),header->strLen));
    file.setFileName(filename);
    file.open(QIODevice::WriteOnly);
}
quint64 FileHansz::writeBytes(char *data, quint64 size){
    return file.write(data,size);
}
quint64 FileHansz::readBytes(char *buffer, quint64 size){
    return file.read(buffer,size);
}
}
