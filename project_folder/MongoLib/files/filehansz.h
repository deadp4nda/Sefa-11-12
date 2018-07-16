#ifndef FILEHANSZ_H
#define FILEHANSZ_H

#include <iostream>
#include <QFile>
#include <QString>
#include <QDir>
#include <QTimer>
#include "mongolib_global.h"

namespace Mongo {
class MONGOLIBSHARED_EXPORT FileHansz: public QObject{
    Q_OBJECT
public:
    FileHansz(const QFile& file,quint64 filetype);
    FileHansz(const QDir &stdDir);
    FileHansz(const FileHansz&) = delete;
    int addData(const QByteArray&);
    bool isBroken()const{return broken;}

public: //Getter
    const QByteArray getHeaders()const{return headers;}
    const QString getName()const{return name;}
    QFile* getFile(){return &file;}
    quint64 getFileType()const{return filetype;}
    quint64 getFileSize()const{return fileSize;}
    quint64 getStringSize()const{return stringSize;}
private:
    QFile file;
    QString name;
    quint64 filetype;
    QByteArray headers;
    QDir stdDir;
    bool broken = false;
    QByteArray buffer;
    QTimer timer;
    quint64 fileSize = 0;
    quint64 stringSize = 0;
    bool mode = false; //true == sending, false == receiving
private:
    void refactorHeaders();
private slots:
    void update();
signals:
    void fileTransmissionComplete();
};
}

#endif // FILEHANSZ_H
