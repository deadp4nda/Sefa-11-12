#include "datahansz.h"
#include "mngthmanager.h"
#include <memory>
#include <QFile>

namespace Mongo{
DataHansz::~DataHansz(){

    if(file)
        delete file;
    else if(inst)
        delete inst;
    else if(stuff)
        delete stuff;
}
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
    Mongo_Header header;
    header.mng_type = spec;
    header.payload = sizeof(Mongo_Header);
    stuff =
            new StuffHansz(
                std::shared_ptr<QByteArray>(
                    new QByteArray((char*)&header,sizeof(Mongo_Header))
                    )
                );
}
DataHansz::DataHansz(const SafeByteArray headerBuf){
    Mongo_Header *whichone = (Mongo_Header*)headerBuf->constData();
    specifier = whichone->mng_type;
    switch(whichone->mng_type){
    case MONGO_TYPE_INST:
        inst = new InstructionHansz(headerBuf);
        waitingFor=whichone->payload-headerBuf->size();
        received = headerBuf->size();
        file = nullptr;
        stuff = nullptr;
        break;
    case MONGO_TYPE_FILE:
        file = new FileHansz(headerBuf);
        waitingFor=whichone->payload-headerBuf->size();
        received = headerBuf->size();
        inst = nullptr;
        stuff = nullptr;
        break;
    case MONGO_TYPE_EXIT:
    case MONGO_TYPE_INIT:
    case MONGO_TYPE_UNSP:
        stuff = new StuffHansz(headerBuf);
        waitingFor=whichone->payload-headerBuf->size();
        received = headerBuf->size();
        inst = nullptr;
        file = nullptr;
    case MONGO_TYPE_INVA:
    default:
        stuff = nullptr;
        inst = nullptr;
        file = nullptr;
    }
}
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
SafeByteArray DataHansz::getContent()const{
    switch (specifier) {
    case MONGO_TYPE_INST:
        return inst->getContent();
    case MONGO_TYPE_FILE:
        break;
    case MONGO_TYPE_EXIT:
    case MONGO_TYPE_INIT:
    case MONGO_TYPE_UNSP:
        return stuff->getContent();
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
        received = buffer->size();
        break;
    case MONGO_TYPE_FILE:
        file->addData(buffer);
        received = buffer->size();
        break;
    case MONGO_TYPE_EXIT:
    case MONGO_TYPE_INIT:
    case MONGO_TYPE_UNSP:
        stuff->addData(buffer);
        received = buffer->size();
        break;
    case MONGO_TYPE_INVA:
    default:
        break;
    }
}
StuffHansz::StuffHansz(SafeByteArray arr){
    array=arr;
}
InstructionHansz::InstructionHansz(quint8 instr, quint32 toPrgm,
                                   quint16 args, const QByteArray &content){
    array = SafeByteArray(new QByteArray());
    Mongo_Header mongo;
    mongo.mng_type = MONGO_TYPE_INST;
    mongo.payload = sizeof(mongo)+sizeof(Instruction_Header)+content.size();
    Instruction_Header instruction;
    instruction.args = args;
    instruction.contLen = content.size();
    instruction.exCode = instr;
    instruction.prgmSpec = toPrgm;
    array->append((char*)&mongo,sizeof(mongo));
    array->append((char*)&instruction,sizeof(instruction));
    array->append(content);
}
InstructionHansz::InstructionHansz(const SafeByteArray buffer){
    Instruction_Header *instruction = (Instruction_Header*)(buffer->constData()+sizeof(Mongo_Header));
    this->addressedProgram = instruction->prgmSpec;
    this->instruction = instruction->exCode;
    this->arguments = instruction->args;
    this->contentLength = instruction->contLen;
    array = buffer;
}
void FileHansz::addData(const SafeByteArray buffer){
    file.write(*buffer);
}
SafeByteArray FileHansz::getData(){
    return SafeByteArray(new QByteArray(file.read(2048)));
}
FileHansz::FileHansz(const SafeByteArray){}
FileHansz::FileHansz(QFile &file,quint8 type):
    filetype(type){
    file.open(file.handle(),QIODevice::ReadWrite);
}
FileHansz::~FileHansz(){
    file.close();
}
}
