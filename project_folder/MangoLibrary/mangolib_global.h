#ifndef MONGOLIB_GLOBAL_H
#define MONGOLIB_GLOBAL_H

#include <QtCore/qglobal.h>

//#if defined(MONGOLIB_LIBRARY)
//#  define MONGOLIBSHARED_EXPORT Q_DECL_EXPORT
//#else
//#  define MONGOLIBSHARED_EXPORT Q_DECL_IMPORT
//#endif
#include <QSslSocket>
#include <QTcpServer>
#include <memory>
#include <QByteArray>
#include <QCryptographicHash>

extern "C"{
void ChryHexdump(const char *data_buffer, const unsigned int length,const char *functionName, FILE *output = stdout);
}
QByteArray endingOrder();
QString operator*(const QString & str,qint32 times);
QByteArray fileChecksum(const QString &fileName, QCryptographicHash::Algorithm hashAlg = QCryptographicHash::Sha3_256);
QString /*MONGOLIBSHARED_EXPORT*/ byteArrayToBase32(const QByteArray &array);

class QFile;
class QSslSocket;
class QTcpServer;

namespace Mango{

class MngThManager;
class MangoConnection;
class InstructionHansz;
class FileHansz;

typedef std::shared_ptr<QByteArray> SafeByteArray;
typedef std::shared_ptr<InstructionHansz> SafeInstruction;
typedef std::shared_ptr<FileHansz> SafeFileHansz;

#define MANGO_TYPE_INST (0x10U)
#define MANGO_TYPE_FILE (0x20U)

#define MANGO_INSTRUCTION_MAXIMUM 0xFFFF
#define FILE_READ_MAXLENGTH 0xFFFF

#define FILE_CHECKSUM_LENGTH 64

enum Filetype{
    Undefined = 1,
    Movie,
    Picture,
    Text,
    Audio,
    Broken
};
enum Instructions{
    Exit = 1,           //exit command
    Kill,           //close destination program
    GetFileList,    //get directory of released files
    GetPrgmList,    //get List of Programs with specifiers
    RetrieveFile,   //get a certain File
    Execute,        //Execute Program<spec> with file/argument
    Chat,           //body containing chat msg
    FileToBeSent,   //initiating file transfer
    InvalidInstr    //reserved for invalid transfers
};
enum Program{
    This = 1,
    InvalidPrgm     //reserved for invalid transfers
};
struct /*MONGOLIBSHARED_EXPORT*/ Mongo_Header{
    quint64 mng_type;        //type of data(instruction/file/welcome/etc...)
    quint64 payload;        //size of whole transmission
};

struct /*MONGOLIBSHARED_EXPORT*/ Instruction_Header{
    quint32 exCode;          //instruction code (enum Instructions)
    quint32 args;           //additional arguments
    quint32 prgmSpec;       //program to be called
    quint32 contLen;        //length of the content
};

struct /*MONGOLIBSHARED_EXPORT*/ File_Header{
    quint64 filetype;        //type of file, if registered
    quint64 strLen;         //File name length
    quint64 fileLen;        //File Size
};

}
#endif // MONGOLIB_GLOBAL_H
