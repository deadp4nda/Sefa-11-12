#include "datahansz.h"
#include "mngthmanager.h"
#include <memory>

namespace Mongo{
DataHansz::DataHansz(FileHansz *inHansz):
    specifier(MONGO_TYPE_FILE),file(inHansz){
    inst = nullptr;
    stuff = nullptr;
}
DataHansz::DataHansz(InstructionHansz *inHansz):
    specifier(MONGO_TYPE_INST),inst(inHansz){
    file = nullptr;
    stuff = nullptr;
}
DataHansz::DataHansz(StuffHansz *inHansz):
    specifier(MONGO_TYPE_INVA),stuff(inHansz){
    inst = nullptr;
    file = nullptr;
}
DataHansz::DataHansz(const quint16 spec):
    specifier(spec){
    stuff= new StuffHansz(std::shared_ptr<QByteArray>(new QByteArray((char*)&spec,sizeof(spec))));
}
StuffHansz::StuffHansz(SafeByteArray arr){
    array=arr;
}
InstructionHansz::InstructionHansz(quint8 instr, quint32 toPrgm,
                                   quint16 args, const QByteArray &content){
    array = SafeByteArray(new QByteArray());
}
void FileHansz::addData(const SafeByteArray){}
SafeByteArray  FileHansz::getData()const{}
DataHansz::DataHansz(const SafeByteArray headerBuf){}
SafeByteArray DataHansz::getData()const{
    switch (specifier) {
    case MONGO_TYPE_INST:
        return inst->getData();
    case MONGO_TYPE_FILE:
        break;
    case MONGO_TYPE_EXIT:
    case MONGO_TYPE_INIT:
    case MONGO_TYPE_UNSP:
        return stuff->getData();
    case MONGO_TYPE_INVA:
    default:
        break;
    }
    return SafeByteArray(new QByteArray());
}
void DataHansz::addData(const SafeByteArray buffer){
    switch (specifier) {
    case MONGO_TYPE_INST:
        inst->addData(buffer);
        break;
    case MONGO_TYPE_FILE:
        file->addData(buffer);
        break;
    case MONGO_TYPE_EXIT:
    case MONGO_TYPE_INIT:
    case MONGO_TYPE_UNSP:
        stuff->addData(buffer);
        break;
    case MONGO_TYPE_INVA:
    default:
        break;
    }
}
}
