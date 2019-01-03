#include "filehansz.h"
#include "mangolib_global.h"
#include <QDataStream>
#include <QFile>
#include <QFileInfo>


namespace Mango{
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
        headers.append(hash);
        headers.append(name.toUtf8());
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
}
FileHansz::~FileHansz(){
    if(file.isOpen())file.close();
}
void FileHansz::refactorHeaders(){
    //ChryHexdump(headers.data(),headers.size(),"FileHansz::refactorHeaders",stdout);
    File_Header *header = (File_Header*)(headers.data()+sizeof(Mongo_Header));
    char *rawData = (char*)header;
    filetype = header->filetype;
    fileSize = header->fileLen;
    stringSize = header->strLen;
    hashString = QString::fromLocal8Bit(rawData+sizeof(File_Header), FILE_CHECKSUM_LENGTH);
    hash = QByteArray::fromHex(hashString.toUtf8());
    //qDebug() << "arrived HashString: " << hashString;
    name = QString(QByteArray((char*)header+sizeof(File_Header)+FILE_CHECKSUM_LENGTH,header->strLen));
    file.setFileName(stdDir.absoluteFilePath(hashString));
    file.open(QIODevice::WriteOnly);
}
}
