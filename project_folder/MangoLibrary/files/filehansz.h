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
    FileHansz(const FileHansz&) = delete;                           // explizites löschen des kopierkonstruktors
    ~FileHansz();                                                   // destruktor
    int addData(const QByteArray&, bool isLastPackage = false);     // fügt ein Datenpaket an eine Übertragung an
    bool isBroken()const{return broken;}                            // unwichtig, implementierungsdetail
    void endingOne(){firstEndingSent=true;}                         // unwichtig, implementierungsdetail
    bool getFirstEndingSent()const{return firstEndingSent;}         // unwichtig, implementierungsdetail
    void print(){std::cout << "---FILE---" << "\nName: " << getName().toStdString() << "\nHash: " << getChecksumString().toStdString() << std::endl;}
    // ^eine Ausgabefunktion
public: //Getters
    const QByteArray getHeaders()const{return headers;} // get header
    const QString getName()const{return name;}
    const QByteArray getChecksum()const{return hash;}
    const QString getChecksumString()const{return hash.toHex();}
    QFile* getFile(){return &file;}
    quint64 getFileType()const{return filetype;}
    quint64 getFileSize()const{return fileSize;}
    quint64 getStringSize()const{return stringSize;}
private:
    QTimer timer;                       // memberdaten, die daten speichern. das können sie gut. sehr gut sogar.
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
    void refactorHeaders();                                 // wandelt rohdatenmatsch mit headerinformationen zu headerinformationen ohen rohdatenmatsch
signals:
    void fileTransmissionComplete();
    void fileTransmissionCorrupted();
    friend class MngFileSocket;
};
}

#endif // FILEHANSZ_H
