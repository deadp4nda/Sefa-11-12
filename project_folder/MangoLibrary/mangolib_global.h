#ifndef MONGOLIB_GLOBAL_H
#define MONGOLIB_GLOBAL_H

#include <QtCore/qglobal.h>

/* bemerkung: alle c++ klassen sind so aufgebaut, dass in einem Headerfile (*.h) die Methoden und Membervariablen deklariert sind ,und in einem zugehörigen
 * *.cpp - file implementiert. daher sind nur die *.h - dateien kommentiert, um die Funktion der Funktionen zu beschreiben.
 * es gibt nichts, was ich noch dazu sagen könnte. es ist implementiert was dran steht. wirklich.
*/
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
void ChryHexdump(const char *data_buffer, const unsigned int length,const char *functionName, FILE *output = stdout); // hexdump. für debugging
}
QByteArray endingOrder(); // die Bytesequenz am ende
QString operator*(const QString & str,qint32 times); // strings multiplizieren
QByteArray fileChecksum(const QString &fileName, QCryptographicHash::Algorithm hashAlg = QCryptographicHash::Sha3_256); // Dateiprüfsumme
QString /*MONGOLIBSHARED_EXPORT*/ byteArrayToBase32(const QByteArray &array); // hash zu hash-string

class QFile;
class QSslSocket;
class QTcpServer;

namespace Mango{

class MngThManager;
class MangoConnection;
class InstructionHansz;
class FileHansz;

typedef std::shared_ptr<QByteArray> SafeByteArray;          // smartpointer, damit ich die sache nicht zu sehr verhauen kann
typedef std::shared_ptr<InstructionHansz> SafeInstruction;  // ^
typedef std::shared_ptr<FileHansz> SafeFileHansz;           // ^

#define MANGO_TYPE_INST (0x10U)             //Übertragung = Anweisung
#define MANGO_TYPE_FILE (0x20U)             // -||-       = Datei

#define MANGO_INSTRUCTION_MAXIMUM 0xFFFF    // maximale größe der anweisungen
#define FILE_READ_MAXLENGTH 0xFFFF          // maximaler Datenblock, der ausgelesen und verschickt wird.

#define FILE_CHECKSUM_LENGTH 64             // datei prüfsummen-länge

enum Filetype{
    Undefined = 1,                          // Dateityp. man siehe sich den anhang der Arbeit an
    Movie,
    Picture,
    Text,
    Audio,
    Broken
};
enum Instructions{              //tja, siehe anhang der arbeit
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
enum Program{                     //tja, siehe anhang der arbeit
    This = 1,
    InvalidPrgm     //reserved for invalid transfers
};
struct /*MONGOLIBSHARED_EXPORT*/ Mongo_Header{ // header für die übertragungstypen, der vorne drangehangen wird.
    quint64 mng_type;        //type of data(instruction/file/etc...)
    quint64 payload;        //size of whole transmission
};

struct /*MONGOLIBSHARED_EXPORT*/ Instruction_Header{ // headerstruct für anweisungen
    quint32 exCode;          //instruction code (enum Instructions)
    quint32 args;           //additional arguments
    quint32 prgmSpec;       //program to be called
    quint32 contLen;        //length of the content
};

struct /*MONGOLIBSHARED_EXPORT*/ File_Header{ // headerstruct für dateien
    quint64 filetype;        //type of file, if registered
    quint64 strLen;         //File name length
    quint64 fileLen;        //File Size
};

}
#endif // MONGOLIB_GLOBAL_H
