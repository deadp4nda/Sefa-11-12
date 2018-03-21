#ifndef DATAHANSZ_H
#define DATAHANSZ_H

#include "mongolib_global.h"
#include <QObject>
#include <memory>
#include <QFile>

namespace  Mongo{
class MONGOLIBSHARED_EXPORT FileHansz{
public:
    void addData(const SafeByteArray);
    SafeByteArray getData()const;
private:
    QFile file;
    quint8 filetype;
};
class MONGOLIBSHARED_EXPORT InstructionHansz{
public:
    InstructionHansz(SafeByteArray);
    InstructionHansz(quint8 instr, quint32 toPrgm, quint16 args,
                     const QByteArray &content = QByteArray());
    SafeByteArray getData()const{return array;}
    void addData(const SafeByteArray inArray){array->append(*inArray);}
private:
    SafeByteArray array;
    quint8 instruction;
    quint32 addressedProgram;
};
class MONGOLIBSHARED_EXPORT StuffHansz{
public:
    StuffHansz(SafeByteArray);
    SafeByteArray getData()const{return array;}
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
    void addData(const SafeByteArray);
    SafeByteArray getData() const;
private:
    quint16 specifier = MONGO_TYPE_INVA;
    FileHansz *file;
    InstructionHansz *inst;
    StuffHansz *stuff;
};
}
#endif // DATAHANSZ_H
