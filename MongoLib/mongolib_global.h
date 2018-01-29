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

class MngManager;
class MngServer;
class MngClient;

#define MONGO_TYPE_WELC 0x10
#define MONGO_TYPE_ISTR 0x20
#define MONGO_TYPE_FILE 0x30
#define MONGO_TYPE_UNSP 0xFF
#define MONGO_TYPE_EXIT 0x40
    
#define MONGO_INSTR_ARG_SYS 0x00

enum TypeOfData{
    Welcome,
    Instr,
    File,
    Unspecified,
    Exit
};
    
enum MONGOLISBSHARED_EXPORT InstrType{
    GetFileList,
    GetPrgmList//etc
};
struct Mongo_Hdr{
    unsigned char mng_type; //type of data(instruction/file/welcome/etc...)
};

struct MONGOLIBSHARED_EXPORT Instruction{
    unsigned char instruction;      // execution code
    unsigned int toProgram;         //program aspect or program that is to be called
    unsigned char args;             //additional arguments
    unsigned int strLen;            //length of the file name
//    wchar_t withFile[FILENAME_MAX]; /// file name is contained by packet data->too heavy
};

struct MONGOLIBSHARED_EXPORT FileStreamHdr{
    unsigned int strLen;            //
    unsigned char filetype;
//    wchar_t fileName[FILENAME_MAX]; ///same here, will be sent with the first packet of a new stream
};

}
#endif // MONGOLIB_GLOBAL_H
