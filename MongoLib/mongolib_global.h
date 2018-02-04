#ifndef MONGOLIB_GLOBAL_H
#define MONGOLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MONGOLIB_LIBRARY)
#  define MONGOLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MONGOLIBSHARED_EXPORT Q_DECL_IMPORT
#endif
#include <QTcpSocket>
#include <QTcpServer>

class QFile;
class QTcpSocket;
class QTcpServer;

namespace Mongo{

class MngThManager;
class MngServer;
class MngClient;

#define MONGO_TYPE_INIT ((unsigned int)0x08)
#define MONGO_TYPE_INST ((unsigned int)0x10)
#define MONGO_TYPE_FILE ((unsigned int)0x20)
#define MONGO_TYPE_UNSP ((unsigned int)0xFF)
#define MONGO_TYPE_EXIT ((unsigned int)0x40)

enum TypeOfData{
    Welcome,
    Instr,
    File,
    Unspecified,
    Exit
};
enum Instructions{
    Kill,           //close destination
    GetFileList,    //get directory of released files
    GetPrgmList,    //get List of Programs with specifiers
    RetrieveFile,   //get a certain File
    Execute,        //Execute Program<spec> with file/argument
    Chat            //body containing chat msg
};

struct Mongo_Hdr{
    quint8 mng_type; //type of data(instruction/file/welcome/etc...)
};

struct MONGOLIBSHARED_EXPORT Instruction_header{
    quint8 exCode;           //instruction code (MONGO_INSTR_....)
    quint32 prgmSpec;         //program to be called
    quint8 args;             //additional arguments
    quint32 contLen;           //length of the content
};

struct MONGOLIBSHARED_EXPORT File_header{
    quint8 filetype;         //type of file, if registered
    quint32 strLen;            //File name length
};

}
#endif // MONGOLIB_GLOBAL_H
