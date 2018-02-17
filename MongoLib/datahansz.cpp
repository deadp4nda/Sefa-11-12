#include "datahansz.h"
#include <QFile>

namespace Mongo{

DataHansz::DataHansz(QByteArray *buf){
    Mongo_Hdr *hdr = (Mongo_Hdr*)buf->data();
    quint8 spec = hdr->mng_type;
    char *content = (char*)buf->data()+sizeof(Mongo_Hdr);
    unsigned int size = buf->size()-sizeof(Mongo_Hdr);
    switch(spec){
    case MONGO_TYPE_EXIT:
        typeString = "EXIT";
        arr = QByteArray(content,size);
        break;
    case MONGO_TYPE_FILE:
        typeString = "FILE";
        arr = QByteArray(content+sizeof(File_header)+((File_header*)content)->strLen,
                         size   -sizeof(File_header)-((File_header*)content)->strLen);
        break;
    case MONGO_TYPE_INIT:
        typeString = "INIT";
        arr = QByteArray(content,size);
        break;
    case MONGO_TYPE_INST:
        typeString = "INST";
        arr = QByteArray(content+sizeof(Instruction_header)+((Instruction_header*)content)->contLen,
                         size   -sizeof(Instruction_header)-((Instruction_header*)content)->contLen);
        break;
    case MONGO_TYPE_UNSP:
    default:
        typeString = "UNSP";
        arr = QByteArray(content, size);
        break;
    }
}
FileHansz::FileHansz(QByteArray *buf):DataHansz(buf){
    File_header *file = (File_header*)buf->data();
    filetype = file->filetype;
    unsigned int jmp = sizeof(File);
    char *tail = buf->data()+jmp;
    filename = QString(QByteArray(tail,file->strLen));
}
InstructionHansz::InstructionHansz(QByteArray *buf):DataHansz(buf){
    char *origin = buf->data();
    Instruction_header *in = (Instruction_header*)origin;
    this->exCode = in->exCode;
    this->args = in->args;
    this->toProgram = in->prgmSpec;
}
DataHansz::DataHansz(quint8 type, QByteArray *buf):spec(type){
    if(buf!=nullptr){
        arr = QByteArray(*buf);
    }
    switch(spec){
    case MONGO_TYPE_EXIT:
        typeString = "EXIT";
        break;
    case MONGO_TYPE_FILE:
        typeString = "FILE";
        break;
    case MONGO_TYPE_INIT:
        typeString = "INIT";
        break;
    case MONGO_TYPE_INST:
        typeString = "INST";
        break;
    case MONGO_TYPE_UNSP:
    default:
        typeString = "UNSP";
        break;
    }
}
FileHansz::FileHansz(QFile &file, quint8 type): DataHansz(MONGO_TYPE_FILE),filename(file.fileName()),filetype(type){
    QString tmp = file.fileName();
    QString name;
    for(int i = tmp.size(); i > 0;i--){
        if(tmp[i-1] == "/" || tmp[i-1] == "\\"){
            break;
        }
        name.prepend(tmp[i]);
    }
    File_header h= {
        type,
        (quint32)name.toUtf8().size()
    };
    arr.append((char*)&h,sizeof(h));
    arr.append(name.toUtf8());
    arr.append(file.readAll());
}
InstructionHansz::InstructionHansz(quint8 exCode, quint32 prgmCode, quint8 args, QByteArray *buf): DataHansz(MONGO_TYPE_INST),exCode(exCode),toProgram(prgmCode),args(args){
    Instruction_header h = {
        exCode,
        prgmCode,
        args,
        (quint32)buf->length()
    };
    arr.append((char*)&h,sizeof(Instruction_header));
    arr.append(*buf);
}
}
