#include "mangolib_global.h"
#include <string>
#include <QFile>

using std::string;

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

#include <inttypes.h>
#include <string.h>
extern "C"{
int base64encode(const void* data_buf, size_t dataLength, char* result, size_t resultSize)
{
   const char base64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789()";
   const uint8_t *data = (const uint8_t *)data_buf;
   size_t resultIndex = 0;
   size_t x;
   uint32_t n = 0;
   int padCount = dataLength % 3;
   uint8_t n0, n1, n2, n3;

   /* increment over the length of the string, three characters at a time */
   for (x = 0; x < dataLength; x += 3)
   {
      /* these three 8-bit (ASCII) characters become one 24-bit number */
      n = ((uint32_t)data[x]) << 16; //parenthesis needed, compiler depending on flags can do the shifting before conversion to uint32_t, resulting to 0

      if((x+1) < dataLength)
         n += ((uint32_t)data[x+1]) << 8;//parenthesis needed, compiler depending on flags can do the shifting before conversion to uint32_t, resulting to 0

      if((x+2) < dataLength)
         n += data[x+2];

      /* this 24-bit number gets separated into four 6-bit numbers */
      n0 = (uint8_t)(n >> 18) & 63;
      n1 = (uint8_t)(n >> 12) & 63;
      n2 = (uint8_t)(n >> 6) & 63;
      n3 = (uint8_t)n & 63;

      /*
       * if we have one byte available, then its encoding is spread
       * out over two characters
       */
      if(resultIndex >= resultSize) return 1;   /* indicate failure: buffer too small */
      result[resultIndex++] = base64chars[n0];
      if(resultIndex >= resultSize) return 1;   /* indicate failure: buffer too small */
      result[resultIndex++] = base64chars[n1];

      /*
       * if we have only two bytes available, then their encoding is
       * spread out over three chars
       */
      if((x+1) < dataLength)
      {
         if(resultIndex >= resultSize) return 1;   /* indicate failure: buffer too small */
         result[resultIndex++] = base64chars[n2];
      }

      /*
       * if we have all three bytes available, then their encoding is spread
       * out over four characters
       */
      if((x+2) < dataLength)
      {
         if(resultIndex >= resultSize) return 1;   /* indicate failure: buffer too small */
         result[resultIndex++] = base64chars[n3];
      }
   }

   /*
    * create and add padding that is required if we did not have a multiple of 3
    * number of characters available
    */
   if (padCount > 0)
   {
      for (; padCount < 3; padCount++)
      {
         if(resultIndex >= resultSize) return 1;   /* indicate failure: buffer too small */
         result[resultIndex++] = '=';
      }
   }
   if(resultIndex >= resultSize) return 1;   /* indicate failure: buffer too small */
   result[resultIndex] = 0;
   return 0;   /* indicate success */
}
}
QString byteArrayToBase32(const QByteArray &array){
//    const char *arrayData = array.data();
//    qDebug() << array.toHex();
//    char buffer[512] = {12};
//    qDebug() << base64encode(arrayData,array.size(),buffer,512);
//    QString convertedKey = QString::fromLatin1(buffer);
//    qDebug() << convertedKey;
//    convertedKey = convertedKey.prepend("x"+QString("0")*((FILE_CHECKSUM_LENGTH-1)-convertedKey.length()));
    return array.toHex();
}
