#ifndef FILEHANSZ_H
#define FILEHANSZ_H

#include <iostream>
#include <QFile>
#include <QString>
#include <QDir>
#include "mongolib_global.h"

namespace Mongo {
class MONGOLIBSHARED_EXPORT FileHansz{
public:
    FileHansz(const QFile& file,quint64 filetype);
    FileHansz(const QDir &stdDir);
    FileHansz(const FileHansz&) = delete;
    void addData(SafeByteArray);

    const QString getName()const{return name;}
    quint64 getFileType()const{return filetype;}
    QFile* getFile(){return &file;}
    QByteArray getHeaders()const{return headers;}
private:
    QFile file;
    QString name;
    quint64 filetype;
    QByteArray headers;
    QDir stdDir;
private:
    void refactorHeaders();
};
}

#endif // FILEHANSZ_H
