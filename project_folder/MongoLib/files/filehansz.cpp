#include "filehansz.h"
#include "mongolib_global.h"
#include <QFile>
#include <QFileInfo>

namespace Mongo{
FileHansz::FileHansz(const QFile &file, quint64 filetype):
    file(file.fileName()),filetype(filetype){
    this->file.open(QIODevice::ReadOnly);
    Mongo_Header mongoH;
    File_Header fileH;
    QFileInfo info(file);
    name = info.fileName();
    memset(&mongoH,0,sizeof(Mongo_Header));
    memset(&fileH,0,sizeof(File_Header));
    mongoH.mng_type = MONGO_TYPE_FILE;
    fileH.fileLen = file.size();
    fileH.filetype = filetype;
    fileH.strLen = name.toLocal8Bit().size();
    mongoH.payload = sizeof(mongoH)+sizeof(fileH)+fileH.strLen+fileH.fileLen;

    headers.append((char*)&mongoH,sizeof(mongoH));
    headers.append((char*)&fileH,sizeof(fileH));
    headers.append(name.toLocal8Bit());
}

FileHansz::FileHansz(const QDir &stdDir):
    stdDir(stdDir){}
void FileHansz::addData(SafeByteArray buffer){
    if(headers.isEmpty()){
        headers = *buffer;
        refactorHeaders();
    }else{
        file.write(*buffer);
    }
}
void FileHansz::refactorHeaders(){
    File_Header *header = (File_Header*)headers.data()+sizeof(Mongo_Header);
    filetype = header->filetype;
    name = QString(QByteArray((char*)header+sizeof(File_Header),header->strLen));
    file.setFileName(stdDir.absoluteFilePath(name));
    file.open(QIODevice::ReadWrite);
}
}
