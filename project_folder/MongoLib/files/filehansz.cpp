#include "filehansz.h"
#include "mongolib_global.h"
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
        broken = false;
    }else{
        filetype = Broken;
        fileSize = 0;
        headers = QByteArray();
        broken = true;
    }
    mode = true;
    QObject::connect(&timer,&QTimer::timeout,this,&FileHansz::update);
    timer.start(5);
}
void FileHansz::update(){
    if(!mode && !buffer.isEmpty() && file.isOpen() && file.isWritable()){
        int size = buffer.size();
        file.write(buffer.data(),size);
        buffer = buffer.right(buffer.size()-size);
    }
    if(!mode && file.size() == fileSize){
        emit fileTransmissionComplete();
        file.close();
    }
}
FileHansz::FileHansz(const QDir &stdDir):
    stdDir(stdDir){
    mode = false;
    QObject::connect(&timer,&QTimer::timeout,this,&FileHansz::update);
    timer.start(5);
}

int FileHansz::addData(const QByteArray &buffer){
    qDebug() <<"@addData with " << buffer.size() << " Bytes";
    if(headers.isEmpty()){
        headers = buffer;
        refactorHeaders();
        return 0;
    }else{
        this->buffer.append(buffer);
        return 2;
    }
}
void FileHansz::refactorHeaders(){
    File_Header *header = (File_Header*)(headers.data()+sizeof(Mongo_Header));
    filetype = header->filetype;
    fileSize = header->fileLen;
    stringSize = header->strLen;
    name = QString(QByteArray((char*)header+sizeof(File_Header),header->strLen));
    file.setFileName(stdDir.absoluteFilePath(name));
    file.open(QIODevice::WriteOnly);
}
}
