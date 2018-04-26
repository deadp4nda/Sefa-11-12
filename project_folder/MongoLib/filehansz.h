#ifndef FILEHANSZ_H
#define FILEHANSZ_H

#include <iostream>
#include <QFile>
#include <QString>
#include "mongolib_global.h"

namespace Mongo {
class MONGOLIBSHARED_EXPORT FileHansz{
public:
    FileHansz(const QFile& file,quint64 filetype);
    FileHansz(const SafeByteArray array);
    FileHansz(const FileHansz&) = delete;
    SafeByteArray getData();
    void addData(SafeByteArray);

    const QString getName()const{return name;}
    quint64 getFileType()const{return filetype;}
    const QFile* getFile()const{return &file;}
private:
    QFile file;
    QString name;
    quint64 filetype;
    bool headerSent = false;
    SafeByteArray headers;
};
}

#endif // FILEHANSZ_H
