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
    FileHansz(const QDir &stdDir);
    FileHansz(const FileHansz&) = delete;
    ~FileHansz();
    int addData(const QByteArray&, bool isLastPackage = false);
    bool isBroken()const{return broken;}
    void endingOne(){firstEndingSent=true;}
    bool getFirstEndingSent()const{return firstEndingSent;}
public: //Getters
    const QByteArray getHeaders()const{return headers;}
    const QString getName()const{return name;}
    const QByteArray getChecksum()const{return hash;}
    const QString getChecksumString()const{return hash.toHex();}
    QFile* getFile(){return &file;}
    quint64 getFileType()const{return filetype;}
    quint64 getFileSize()const{return fileSize;}
    quint64 getStringSize()const{return stringSize;}
private:
    QTimer timer;
    QFile file;
    QDir stdDir;
    QByteArray headers = QByteArray();
    QByteArray hash = QByteArray();

    QString name;
    quint64 fileSize = 0;
    quint64 filetype;
    quint64 stringSize = 0;

    bool firstEndingSent = false;
    bool broken = false;
    bool mode = false; //true == sending, false == receiving
private:
    void refactorHeaders();
signals:
    void fileTransmissionComplete();
    void fileTransmissionCorrupted();
    friend class MngFileSocket;
};
}

#endif // FILEHANSZ_H
