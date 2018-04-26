#include "datahansz.h"
#include "mngthmanager.h"
#include <memory>
#include <QFile>
#include <QFileInfo>
#include <iostream>

namespace Mongo{
//DataHansz::~DataHansz(){

//    if(file)
//        delete file;
//    else if(inst)
//        delete inst;
//    else if(stuff)
//        delete stuff;
//}
//DataHansz::DataHansz(SafeFileHansz inHansz):
//    specifier(MONGO_TYPE_FILE),file(inHansz){
//    inst = nullptr;
//    stuff = nullptr;
//}
//DataHansz::DataHansz(InstructionHansz *inHansz):
//    specifier(MONGO_TYPE_INST),inst(inHansz){
//    file = nullptr;
//    stuff = nullptr;
//}
//DataHansz::DataHansz(StuffHansz *inHansz):
//    specifier(MONGO_TYPE_INVA),stuff(inHansz){
//    inst = nullptr;
//    file = nullptr;
//}
//DataHansz::DataHansz(const quint16 spec):
//    specifier(spec){
//    Mongo_Header header;
//    header.mng_type = spec;
//    header.payload = MONGOHEADER_SIZE;
//    stuff =
//            new StuffHansz(
//                SafeByteArray(
//                    new QByteArray((char*)&header,MONGOHEADER_SIZE)
//                    )
//                );
//}
//DataHansz::DataHansz(const SafeByteArray headerBuf){
//    Mongo_Header *whichone = (Mongo_Header*)headerBuf->constData();
//    specifier = whichone->mng_type;
//    switch(whichone->mng_type){
//    case MONGO_TYPE_INST:
//        inst = new InstructionHansz(headerBuf);
//        waitingFor=whichone->payload-headerBuf->size();
//        received = headerBuf->size();
//        file = nullptr;
//        stuff = nullptr;
//        break;
//    case MONGO_TYPE_FILE:
//        file = new FileHansz(headerBuf);
//        waitingFor=whichone->payload-headerBuf->size();
//        received = headerBuf->size();
//        inst = nullptr;
//        stuff = nullptr;
//        break;
//    case MONGO_TYPE_EXIT:
//    case MONGO_TYPE_INIT:
//    case MONGO_TYPE_UNSP:
//        stuff = new StuffHansz(headerBuf);
//        waitingFor=whichone->payload-headerBuf->size();
//        received = headerBuf->size();
//        inst = nullptr;
//        file = nullptr;
//    case MONGO_TYPE_INVA:
//    default:
//        stuff = nullptr;
//        inst = nullptr;
//        file = nullptr;
//    }
//}
//SafeByteArray DataHansz::getData()const{
//    switch (specifier) {
//    case MONGO_TYPE_INST:
//        return inst->getData();
//    case MONGO_TYPE_FILE:
//        return file->getData();
//        break;
//    case MONGO_TYPE_EXIT:
//    case MONGO_TYPE_INIT:
//    case MONGO_TYPE_UNSP:
//        return stuff->getData();
//    case MONGO_TYPE_INVA:
//    default:
//        break;
//    }
//    return SafeByteArray(new QByteArray());
//}
//SafeByteArray DataHansz::getContent()const{
//    try{
//        switch (specifier) {
//        case MONGO_TYPE_INST:
//            return inst->getContent();
//        case MONGO_TYPE_FILE:
//            break;
//        case MONGO_TYPE_EXIT:
//        case MONGO_TYPE_INIT:
//        case MONGO_TYPE_UNSP:
//            return stuff->getContent();
//        case MONGO_TYPE_INVA:
//        default:
//            break;
//        }
//        return SafeByteArray(new QByteArray());
//    }catch(std::out_of_range range){
//        std::cerr << range.what();
//        return SafeByteArray(new QByteArray());
//    }
//}
//void DataHansz::addData(const SafeByteArray buffer){
//    switch (specifier) {
//    case MONGO_TYPE_INST:
//        inst->addData(buffer);
//        received += buffer->size();
//        break;
//    case MONGO_TYPE_FILE:
//        file->addData(buffer);
//        received += buffer->size();
//        break;
//    case MONGO_TYPE_EXIT:
//    case MONGO_TYPE_INIT:
//    case MONGO_TYPE_UNSP:
//        stuff->addData(buffer);
//        received += buffer->size();
//        break;
//    case MONGO_TYPE_INVA:
//    default:
//        break;
//    }
//}

////StuffHansz
//StuffHansz::StuffHansz(const SafeByteArray arr){
//    array=arr;
//}

////InstructionHansz
////InstructionHansz::InstructionHansz(quint8 instr, quint32 toPrgm,
////                                   quint16 args, const QByteArray &content):
////instruction(instr),addressedProgram(toPrgm),arguments(args),contentLength(content.size()){
////    array = SafeByteArray(new QByteArray());
////    Mongo_Header mongo;
////    Instruction_Header instruction;
////    mongo.mng_type = MONGO_TYPE_INST;
////    instruction.args = arguments;
////    instruction.contLen = contentLength;
////    instruction.exCode = this->instruction;
////    instruction.prgmSpec = addressedProgram;
////    mongo.payload = sizeof(mongo)+INSTRUCTIONHEADER_SIZE+content.size()<MONGO_INSTRUCTION_MAXIMUM?content.size():MONGO_INSTRUCTION_MAXIMUM;
////    array->append((char*)&mongo,sizeof(mongo));
////    array->append((char*)&instruction,sizeof(instruction));
////    if(content.size() <= MONGO_INSTRUCTION_MAXIMUM)
////        array->append(content);
////    else
////        array->append(content.constData(),MONGO_INSTRUCTION_MAXIMUM);
////}
////InstructionHansz::InstructionHansz(const SafeByteArray buffer){
////    Instruction_Header *instruction = (Instruction_Header*)(buffer->constData()+MONGOHEADER_SIZE);
////    this->addressedProgram = instruction->prgmSpec;
////    this->instruction = instruction->exCode;
////    this->arguments = instruction->args;
////    this->contentLength = instruction->contLen;
////    array = buffer;
////}

////FileHansz
//void FileHansz::addData(const SafeByteArray buffer){
//    file.write(*buffer);
//}
//SafeByteArray FileHansz::getData(){
//    if(!headerSent){
//        SafeByteArray array(new QByteArray);
//        array->append(*header);
//        array->append(QByteArray(file.read(MONGO_INSTRUCTION_MAXIMUM-array->size())));
//        stalled -= array->size();
//        finished += array->size();
//    }
//    SafeByteArray array(new QByteArray(file.read(MONGO_INSTRUCTION_MAXIMUM)));
//    stalled -= array->size();
//    finished += array->size();
//    return array;
//}
//FileHansz::FileHansz(const SafeByteArray header){
//    Mongo_Header *Mheader = (Mongo_Header*)(header->constData());
//    File_Header *Fheader = (File_Header*)(header->constData()+MONGOHEADER_SIZE);
//}
//FileHansz::FileHansz(QFile &file,quint8 type):
//    filetype(type){
//    file.open(file.handle(),QIODevice::ReadWrite);
//    File_Header fHeader;
//    QFileInfo info(file);
//    fHeader.fileLen = stalled;
//    fHeader.filetype = type;
//    fHeader.strLen = info.fileName().length();
//    this->header = SafeByteArray(new QByteArray((char*)&fHeader,sizeof(fHeader)));
//    this->header->append(info.fileName());
//    stalled = file.size()+header->size();
//}
//FileHansz::~FileHansz(){
//    file.close();
//}
}
