#include "mongolib_global.h"

#include <QFile>

extern "C"{
void ChryHexdump(const char *data_buffer, const unsigned int length, const char *functionName, FILE *output){
    fprintf(output,"\nNew dump from %s:\n", functionName);
    unsigned char byte;
    unsigned int i, j;
    for (i=0;i < length; i++){
        byte = data_buffer[i];
        fprintf(output,"%02x ",byte);
        if((i%16)==15||(i==length-1)){
            for(j=0; j< 15-(i%16); j++)
                fprintf(output,"   ");
            fprintf(output,"| ");
            for(j=(i-(i%16));j<=i;j++){
                byte = data_buffer[j];
                if((byte>31)&& (byte <127))
                    fprintf(output,"%c",byte);
                else
                    fprintf(output,".");
            }
            fprintf(output,"\n");
        }
    }
}
}
QString operator*(const QString & str,qint32 times){
    QString retVal;
    for(int i = 0;i < times; i++){
        retVal+=str;
    }
    return retVal;
}
QByteArray endingOrder(){
    QByteArray arr(4096,0);
//    arr[10] = '\n';
//    arr[40] = '\n';
//    arr[80] = '\n';
//    for(int i = 0; i < 100; i++){
//        arr[81+i] = '^';
//    }
//    arr[511] = '.';
    return arr;
}
QByteArray fileChecksum(const QString &fileName, QCryptographicHash::Algorithm hashAlg){
    QFile file(fileName);
    if(file.open(QFile::ReadOnly)){
        QCryptographicHash hash(hashAlg);
        if(hash.addData(&file)){
            return hash.result();
        }
    }
    return QByteArray();
}

QString byteArrayToBase32(const QByteArray &array){
    QString returnValue;
    quint64 *temporary  = (quint64*)array.data();
    returnValue += QString::number(*temporary,32);
    temporary = temporary+64;
    returnValue += QString::number(*temporary,32);
    temporary = temporary+64;
    returnValue += QString::number(*temporary,32);
    temporary = temporary+64;
    returnValue += QString::number(*temporary,32);
    return returnValue;

}
