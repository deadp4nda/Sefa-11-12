#ifndef INSTRUCTIONHANSZ_H
#define INSTRUCTIONHANSZ_H

#include <mongolib_global.h>
#include <iostream>

#define HEADERSIZE (sizeof(Mongo_Header)+sizeof(Instruction_Header))

namespace Mongo {
class MONGOLIBSHARED_EXPORT InstructionHansz{
public:
    InstructionHansz(const SafeByteArray input);
    InstructionHansz(quint32 instr,quint32 toPrgm = Program::This,quint32 args = 0,
                     const QByteArray &payload = QByteArray());
    SafeByteArray getAllData()const{return allData;}
    SafeByteArray getPayload();
    bool transactionFinished()const{return stalled == processed;}
private:
    void processInput();
private:
    SafeByteArray allData;
    quint32 instruction = 0;
    quint32 addressedProgram = 0;
    quint32 arguments = 0;
    quint32 contentLength = 0;
    quint32 stalled = 0;
    quint32 processed = 0;
public:
    quint32 getInstructionCode()const{return instruction;}
    quint32 getAddressedProgram()const{return addressedProgram;}
    quint32 getPassedArguments()const{return arguments;}
    quint32 getContentLength()const{return contentLength;}
};
}

#undef HEADERSIZE
#endif // INSTRUCTIONHANSZ_H
