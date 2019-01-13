#ifndef FILEHANSZ_H
#define FILEHANSZ_H

#include <iostream>
#include <QFile>
#include <QString>
#include <QDir>
#include <QTimer>
#include <QDataStream>

#include "mangolib_global.h"


namespace Mango {
class MngFileSocket;
class MngRecvFileSocket;
class /*MONGOLIBSHARED_EXPORT*/ FileHansz: public QObject{ // Dateiobjektzugriff, erbt funktionen für Signale und Slots
    Q_OBJECT
public:
    FileHansz(const QFile& file,quint64 filetype);                  // nehmen Dateizugriffsobjekt, Konstruktor auf der sendenden Seite
    FileHansz(const QDir &stdDir);                                  // nimmt standardspeicher, Konstruktor auf der empfangenden Seite
    FileHansz(const FileHansz&) = delete;                           // explizites löschen des Standardkonstruktors
    ~FileHansz();                                                   // destruktor
    int addData(const QByteArray&, bool isLastPackage = false);
    bool isBroken()const{return broken;}
    void endingOne(){firstEndingSent=true;}
    bool getFirstEndingSent()const{return firstEndingSent;}
    void print(){std::cout << "---FILE---" << "\nName: " << getName().toStdString() << "\nHash: " << getChecksumString().toStdString() << std::endl;}
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
    QString hashString = QString();

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
