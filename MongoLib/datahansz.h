#ifndef DATAHANSZ_H
#define DATAHANSZ_H

#include <QObject>
#include <mongolib_global.h>
namespace  Mongo{
class MONGOLIBSHARED_EXPORT DataHansz
{
public:
    DataHansz(QByteArray *);
    DataHansz(quint8 type, QByteArray *buf = nullptr);
    QString getTypeString() const {
        return typeString;
    }
    quint8 getSpec()const{
        return spec;
    }
    const QByteArray *getContentBuffer()const{
        return &arr;
    }
protected:
    quint8 spec;
    QString typeString;
    QByteArray arr;
};

class MONGOLIBSHARED_EXPORT FileHansz: public DataHansz{
public:
    FileHansz(QByteArray*);
    FileHansz(QString fileName);
    FileHansz(QFile &file, quint8 type);
    QString getFilename()const{
        return filename;
    }
    quint8 getFiletype()const{
        return filetype;
    }
private:
    QString filename;
    quint8 filetype;
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
private:
    quint8 exCode;
    quint32 toProgram;
    quint8 args;
};
}
#endif // DATAHANSZ_H
