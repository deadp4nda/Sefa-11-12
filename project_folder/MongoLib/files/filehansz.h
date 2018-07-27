#ifndef FILEHANSZ_H
#define FILEHANSZ_H

#include <iostream>
#include <QFile>
#include <QString>
#include <QDir>
#include <QTimer>
#include <QDataStream>
#include "mongolib_global.h"


namespace Mongo {
class MngFileSocket;
class MngRecvFileSocket;
class MONGOLIBSHARED_EXPORT FileHansz: public QObject{
    Q_OBJECT
public:
    FileHansz(const QFile& file,quint64 filetype);
    FileHansz(const QDir &stdDir, MngRecvFileSocket *par);
    FileHansz(const FileHansz&) = delete;
    ~FileHansz();
    int addData(const QByteArray&, bool isLastPackage = false);
    bool isBroken()const{return broken;}
    void endingOne(){firstEndingSent=true;}
    bool getFirstEndingSent()const{return firstEndingSent;}
public: //Getter
    const QByteArray getHeaders()const{return headers;}
    const QString getName()const{return name;}
    QFile* getFile(){return &file;}
    quint64 getFileType()const{return filetype;}
    quint64 getFileSize()const{return fileSize;}
    quint64 getStringSize()const{return stringSize;}
private:
    bool fileIsToBeClosed = false;
    bool firstEndingSent = false;
    QFile file;
    QDataStream writingStream;
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
    MngRecvFileSocket *socketParent = nullptr;
private:
    void refactorHeaders();
signals:
    void fileTransmissionComplete();
    friend class MngFileSocket;
};
}

#endif // FILEHANSZ_H
