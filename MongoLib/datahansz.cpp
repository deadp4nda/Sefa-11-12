#include "datahansz.h"

namespace Mongo{
DataHansz::DataHansz(QByteArray *arrayPtr){ //right DataOrder
    if(arrayPtr->size() > MONGO_MAX_MEMSIZE){
        spec = MONGO_TYPE_INVA;
        typeString = "IV:S"; //invalid, size overflow
        delete arrayPtr;
        return;
    }
    if(!arrayPtr){
        spec = MONGO_TYPE_INVA;
        typeString = "IV:N"; //invalid nullpointer
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
        if(buf->size()>MONGO_MAX_MEMSIZE-sizeof(type)){
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
}
DataHansz::~DataHansz(){
    if(arr)
        delete arr;
}
InstructionHansz::InstructionHansz(QByteArray *buf):DataHansz(buf){
    if(spec == MONGO_TYPE_INVA){
        return;
    }
    Instruction_header *header = (Instruction_header*)buf->data();
    exCode = header->exCode;
    toProgram = header->prgmSpec;
    args = header->args;
}
InstructionHansz::InstructionHansz(quint8 exCode, quint32 prgmCode, quint8 args, QByteArray *buf):
    DataHansz(MONGO_TYPE_INST,buf),exCode(exCode),toProgram(prgmCode),args(args){
    char *buffer;
    Instruction_header h;
    h.args =args;
    h.contLen = buf?buf->size():0;
    h.exCode = exCode;
    h.prgmSpec = prgmCode;
    buffer = (char*)&h;
    if(arr){
        QByteArray *temp  = new QByteArray(((char*)&spec),sizeof(Mongo_header));
        temp->append(buffer,sizeof(Instruction_header));
        temp->append(*arr);
        delete arr;
        arr = temp;
    }
}
FileHansz::FileHansz(QFile &inFile, quint8 type):
    DataHansz(MONGO_TYPE_FILE,nullptr),file(inFile.fileName()),filetype(type){
    inFile.close();
    for(int i = file.fileName().size()-1;i >= 0 ;i--){
        if(file.fileName()[i]=='\\' || file.fileName()[i]=='/'){
            break;
        }
        filename.prepend(file.fileName()[i]);
    }
}
FileHansz::FileHansz(QString fileName, quint8 type):
    DataHansz(MONGO_TYPE_FILE,nullptr),file(filename),filetype(type){
    for(int i = file.fileName().size()-1;i >= 0 ;i--){
        if(file.fileName()[i]=='\\' || file.fileName()[i]=='/'){
            break;
        }
        filename.prepend(file.fileName()[i]);
    }
}
}
