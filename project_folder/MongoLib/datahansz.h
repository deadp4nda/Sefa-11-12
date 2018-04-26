#ifndef DATAHANSZ_H
#define DATAHANSZ_H

#include "mongolib_global.h"
#include <QObject>
#include <memory>
#include <QFile>

namespace  Mongo{
//class DataHansz;

//class MONGOLIBSHARED_EXPORT FileHansz{
//private:
//    FileHansz(const SafeByteArray);
//public:
//    FileHansz(const FileHansz&) =delete;
//    FileHansz(QFile &file,quint8 type);
//    ~FileHansz();
//    void addData(const SafeByteArray);
//    SafeByteArray getData();
//    bool processingFinished()const{return stalled==0;}
//private:
//    QFile file;
//    bool headerSent = false;
//    SafeByteArray header;
//    quint8 filetype;
//    quint64 stalled = 0;
//    quint64 finished = 0;
//    friend class DataHansz;
//};
//class MONGOLIBSHARED_EXPORT InstructionHansz{
//private:
//    InstructionHansz(const SafeByteArray);
//public:
//    InstructionHansz(quint8 instr, quint32 toPrgm, quint16 args,
//                     const QByteArray &content = QByteArray());
//    SafeByteArray getData()const{return array;}
//    void addData(const SafeByteArray inArray){array->append(*inArray);}
//public:
//    quint8 getInstructionCode()const{return instruction;}
//    quint32 getAddressedProgram()const{return addressedProgram;}
//    quint16 getPassedArguments()const{return arguments;}
//    quint32 getContentLength()const{return contentLength;}
//    SafeByteArray getContent()const{
//        qDebug() << (int)array->size();
//        qDebug() << contentLength;
//        return SafeByteArray(
//                    new QByteArray(
//                        array->constData()+MONGOHEADER_SIZE+INSTRUCTIONHEADER_SIZE,
//                        contentLength)
//                    );
//    }
//private:
//    SafeByteArray array;
//    quint8 instruction;
//    quint32 addressedProgram;
//    quint16 arguments;
//    quint32 contentLength;
//    friend class DataHansz;
//};
//class MONGOLIBSHARED_EXPORT StuffHansz{
//private:
//    StuffHansz(const SafeByteArray);
//public:
//    SafeByteArray getData()const{return array;}
//    SafeByteArray getContent()const{
//        return SafeByteArray(
//                    new QByteArray(array->constData()+MONGOHEADER_SIZE,array->size()-MONGOHEADER_SIZE)
//                    );
//    }
//    void addData(const SafeByteArray inArray){array->append(*inArray);}
//private:
//    SafeByteArray array;
//    friend class DataHansz;
//};


//class MONGOLIBSHARED_EXPORT DataHansz{
//private:
//    DataHansz(const SafeByteArray);
//public:
//    DataHansz(SafeFileHansz );
//    DataHansz(InstructionHansz*);
//    DataHansz(StuffHansz*);
//    DataHansz(const quint16 spec);
//    DataHansz(const DataHansz&) = delete;
//    ~DataHansz();
//    void addData(const SafeByteArray);
//    SafeByteArray getData() const;
//    SafeByteArray getContent() const;
//    bool satisfied()const{return (waitingFor == 0);}
//    quint16 type()const{return specifier;}
//    SafeFileHansz getFileHansz(){return file;}
//    InstructionHansz *getInstructionHansz(){return inst;}
//    StuffHansz *getStuffHansz(){return stuff;}
//private:
//    quint16 specifier = MONGO_TYPE_INVA;
//    SafeFileHansz file = nullptr;
//    InstructionHansz *inst = nullptr;
//    StuffHansz *stuff = nullptr;
//    quint64 waitingFor = 0;
//    quint64 received = 0;
//    friend class MngThManager;
//};
}
#endif // DATAHANSZ_H
