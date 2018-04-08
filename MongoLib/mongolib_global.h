﻿#ifndef MONGOLIB_GLOBAL_H
#define MONGOLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MONGOLIB_LIBRARY)
#  define MONGOLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MONGOLIBSHARED_EXPORT Q_DECL_IMPORT
#endif
#include <QTcpSocket>
#include <QTcpServer>
#include <memory>
#include <QByteArray>


class QFile;
class QTcpSocket;
class QTcpServer;

namespace Mongo{

class MngThManager;
class MngServer;
class MongoConnection;
class DataHansz;

typedef std::shared_ptr<QByteArray> SafeByteArray;
typedef std::shared_ptr<DataHansz> SafeDataHansz;

#define MONGO_TYPE_INIT (0x08U)
#define MONGO_TYPE_INST (0x10U)
#define MONGO_TYPE_FILE (0x20U)
#define MONGO_TYPE_UNSP (0xFFU)
#define MONGO_TYPE_EXIT (0x40U)
#define MONGO_TYPE_INVA (0xB3U)

#define MONGO_INSTRUCTION_MAXIMUM 0xFFFF

enum TypeOfData{
    Welcome,
    Instr,
    File,
    Unspecified,
    Exit
};
enum Filetype{
    Undefined,
    Movie,
    Picture,
    Text,
    Audio
};
enum Instructions{
    Kill,           //close destination program
    GetFileList,    //get directory of released files
    GetPrgmList,    //get List of Programs with specifiers
    RetrieveFile,   //get a certain File
    Execute,        //Execute Program<spec> with file/argument
    Chat,           //body containing chat msg
    InvalidInstr    //reserved for invalid transfers
};
enum Program{
    This,
    InvalidPrgm     //reserved for invalid transfers
};
struct MONGOLIBSHARED_EXPORT Mongo_Header{
    quint8 mng_type;        //type of data(instruction/file/welcome/etc...)
    quint64 payload;        //size of whole transmission
};

struct MONGOLIBSHARED_EXPORT Instruction_Header{
    quint8 exCode;          //instruction code (enum Instructions)
    quint32 prgmSpec;       //program to be called
    quint16 args;           //additional arguments
    quint32 contLen;        //length of the content
};

struct MONGOLIBSHARED_EXPORT File_Header{
    quint8 filetype;        //type of file, if registered
    quint32 strLen;         //File name length
    quint64 fileLen;        //File Size
};

}
#endif // MONGOLIB_GLOBAL_H
