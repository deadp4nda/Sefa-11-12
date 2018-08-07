#include "filehansz.h"
#include "mongolib_global.h"
#include <QDataStream>
#include <QFile>
#include <QFileInfo>


namespace Mongo{
FileHansz::FileHansz(const QFile &file, quint64 filetype):
    file(file.fileName()),filetype(filetype){
    QDir stdPath(file.fileName());
    stdDir = stdPath.current();

    if(file.exists()){
        this->file.open(QIODevice::ReadOnly);
        Mongo_Header mongoH;
        File_Header fileH;
        QFileInfo info(file);

        hash = byteArrayToBase32(fileChecksum(file.fileName())).toLatin1();
        name = info.fileName();
        memset(&mongoH,0,sizeof(Mongo_Header));
        memset(&fileH,0,sizeof(File_Header));
        mongoH.mng_type = MONGO_TYPE_FILE;
        fileH.fileLen = file.size();
        fileH.filetype = filetype;
        fileH.strLen = name.toUtf8().size();
        mongoH.payload = sizeof(mongoH)+sizeof(fileH)+fileH.strLen+fileH.fileLen;

        headers.append((char*)&mongoH,sizeof(mongoH));
        headers.append((char*)&fileH,sizeof(fileH));
        headers.append(name.toUtf8());
        headers.append(hash);
        broken = false;
    }else{
        filetype = Broken;
        fileSize = 0;
        headers = QByteArray();
        broken = true;
    }
    mode = true;
}
FileHansz::FileHansz(const QDir &stdDir):
    stdDir(stdDir){
    mode = false;
}

int FileHansz::addData(const QByteArray &buffer, bool isLastPackage){
    if(buffer.isEmpty())
        return 3;
    if(headers.isEmpty()){
        headers = buffer;
        refactorHeaders();
        return 0;
    }else{
        file.write(buffer);
        file.waitForBytesWritten(INT_MAX);
        return 2;
    }
    if(isLastPackage){
        file.close();
        if(hash != fileChecksum(file.fileName())){
            emit fileTransmissionCorrupted();
        }
    }
}
FileHansz::~FileHansz(){
    if(file.isOpen())file.close();
}
void FileHansz::refactorHeaders(){
    File_Header *header = (File_Header*)(headers.data()+sizeof(Mongo_Header));
    filetype = header->filetype;
    fileSize = header->fileLen;
    stringSize = header->strLen;
    name = QString(QByteArray((char*)header+sizeof(File_Header),header->strLen));
    hash = QByteArray((char*)header+sizeof(File_Header)+header->strLen,16);
    file.setFileName(stdDir.absoluteFilePath(QString(hash)));
    file.open(QIODevice::WriteOnly);
}
}
