#ifndef DATAHANSZ_H
#define DATAHANSZ_H

#include "mongolib_global.h"
#include <QObject>
#include <memory>
#include <QFile>

namespace  Mongo{
class DataHansz;

class MONGOLIBSHARED_EXPORT FileHansz{
public:
    FileHansz(const SafeByteArray);
    FileHansz(const FileHansz&) =delete;
    FileHansz(QFile &file,quint8 type);
    ~FileHansz();
    void addData(const SafeByteArray);
    SafeByteArray getData();
private:
    QFile file;
    quint8 filetype;
};
class MONGOLIBSHARED_EXPORT InstructionHansz{
public:
    InstructionHansz(const SafeByteArray);
    InstructionHansz(quint8 instr, quint32 toPrgm, quint16 args,
                     const QByteArray &content = QByteArray());
    SafeByteArray getData()const{return array;}
    void addData(const SafeByteArray inArray){array->append(*inArray);}
public:
    quint8 getInstructionCode()const{return instruction;}
    quint32 getAddressedProgram()const{return addressedProgram;}
    quint16 getPassedArguments()const{return arguments;}
    quint32 getContentLength()const{return contentLength;}
    SafeByteArray getContent()const{return SafeByteArray(new QByteArray(array->constData()+sizeof(Mongo_Header)+sizeof(Instruction_Header),contentLength));}
private:
    SafeByteArray array;
    quint8 instruction;
    quint32 addressedProgram;
    quint16 arguments;
    quint32 contentLength;
};
class MONGOLIBSHARED_EXPORT StuffHansz{
public:
    StuffHansz(SafeByteArray);
    SafeByteArray getData()const{return array;}
    SafeByteArray getContent()const{return SafeByteArray(new QByteArray(array->constData()+sizeof(Mongo_Header)+sizeof(Instruction_Header),array->size()-sizeof(Mongo_Header)));}
    void addData(const SafeByteArray inArray){array->append(*inArray);}
private:
    SafeByteArray array;
};
class MONGOLIBSHARED_EXPORT DataHansz{
public:
    DataHansz(const SafeByteArray);
    DataHansz(FileHansz*);
    DataHansz(InstructionHansz*);
    DataHansz(StuffHansz*);
    DataHansz(const quint16 spec);
    DataHansz(const DataHansz&) = delete;
    ~DataHansz();
    void addData(const SafeByteArray);
    SafeByteArray getData() const;
    SafeByteArray getContent() const;
    bool satisfied()const{return (waitingFor == 0);}
    quint16 type()const{return specifier;}
    FileHansz *getFileHansz(){return file;}
    InstructionHansz *getInstructionHansz(){return inst;}
    StuffHansz *getStuffHansz(){return stuff;}
private:
    quint16 specifier = MONGO_TYPE_INVA;
    FileHansz *file = nullptr;
    InstructionHansz *inst = nullptr;
    StuffHansz *stuff = nullptr;
    quint64 waitingFor = 0;
    quint64 received = 0;
};
}
#endif // DATAHANSZ_H
