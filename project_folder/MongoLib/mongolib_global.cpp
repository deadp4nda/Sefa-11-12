#include "mongolib_global.h"
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
