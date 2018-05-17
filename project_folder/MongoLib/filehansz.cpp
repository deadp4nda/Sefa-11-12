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
FileHansz::FileHansz(const SafeByteArray array,QDir &stdDir){
    if(array->size() >= sizeof(Mongo_Header)+sizeof(File_Header)){
        Mongo_Header *mongoH = (Mongo_Header*)array->constData();
        File_Header *fileH = (File_Header*)(array->constData()+sizeof(Mongo_Header));
        if(array->size() >= sizeof(Mongo_Header)+sizeof(File_Header)+fileH->strLen){
            QByteArray temp;
            for(quint32 i = sizeof(Mongo_Header)+sizeof(File_Header)-1; i < sizeof(Mongo_Header)+sizeof(File_Header)+fileH->strLen;i++){
                temp.append(array->at(i));
            }
            name = QString::fromLocal8Bit(temp);
            file.setFileName(stdDir.absolutePath()+"/"+name);
            file.open(QIODevice::WriteOnly);
        }else{

        }
    }
}
void FileHansz::addData(SafeByteArray buffer){
    file.write(*buffer);
}
}
