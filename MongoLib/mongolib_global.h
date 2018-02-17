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
/*
 * Byteorder not known
 * problem: large files
 *
*/
#define MONGO_TYPE_INIT (0x08U)
#define MONGO_TYPE_INST (0x10U)
#define MONGO_TYPE_FILE (0x20U)
#define MONGO_TYPE_UNSP (0xFFU)
#define MONGO_TYPE_EXIT (0x40U)

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
