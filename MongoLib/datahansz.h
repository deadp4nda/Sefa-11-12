#ifndef DATAHANSZ_H
#define DATAHANSZ_H

#include <QObject>
#include <mongolib_global.h>
#include <QFile>
namespace  Mongo{
class MONGOLIBSHARED_EXPORT DataHansz
{
public:
    DataHansz(QByteArray *);
    ~DataHansz();
    DataHansz(quint8 type, QByteArray *buf = nullptr);
    QString getTypeString() const {
        return typeString;
    }
    quint8 getSpec()const{
        return spec;
    }
    QByteArray *getWholeBuffer() const{
        return arr;
    }
    QByteArray getContentBuffer() const{
        return QByteArray(arr->data()+sizeof(Mongo_header),arr->size()-sizeof(Mongo_header));
    }
protected:
    quint8 spec;
    QString typeString;
    QByteArray *arr = nullptr;
};

class MONGOLIBSHARED_EXPORT FileHansz: public DataHansz{
public:
    FileHansz(QByteArray*);
    FileHansz(QString fileName, quint8 type);
    FileHansz(QFile &file, quint8 type);
    quint64 writeBytes(char *, quint64);
    quint64 readBytes(char *, quint64);
    quint8 getFiletype()const{
        return filetype;
    }
    const QFile &getFileObject()const{
        return file;
    }
private:
    QFile file;
    quint8 filetype = MONGO_FILETYPE_UNKNOWN;
    QString filename = "";
};

class MONGOLIBSHARED_EXPORT InstructionHansz: public DataHansz {
public:
    InstructionHansz(QByteArray *buf);
    InstructionHansz(quint8 exCode, quint32 prgmCode, quint8 args,QByteArray *buf = nullptr);
    quint8 getInstruction()const{
        return exCode;
    }
    int getProgramID()const{
        return toProgram;
    }
    quint8 getArguments()const{
        return args;
    }
    QByteArray payload()const{
        return QByteArray(arr->data()+sizeof(Instruction_header),arr->size()-sizeof(Instruction_header));
    }
private:
    quint8 exCode = Instructions::InvalidInstr;
    quint32 toProgram = Program::InvalidPrgm;
    quint8 args = 0;
};
}
#endif // DATAHANSZ_H
