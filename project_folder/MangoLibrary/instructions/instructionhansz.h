#ifndef INSTRUCTIONHANSZ_H
#define INSTRUCTIONHANSZ_H

#include "mangolib_global.h"
#include <iostream>

#define HEADERSIZE (sizeof(Mongo_Header)+sizeof(Instruction_Header))

namespace Mango {
class /*MONGOLIBSHARED_EXPORT*/ InstructionHansz{ // Anweisungswrapper, speichert+ verwaltet anweisungen in der Bibliothek
public:
    InstructionHansz(const SafeByteArray input);        // für eingehende anweisungen, kriegt rohdatensalat, der mal header werden will
    InstructionHansz(quint32 instr,quint32 toPrgm = Program::This,quint32 args = 0, //wandelt einzelne Daten in eine Anweisung um
                     const QByteArray &payload = QByteArray());
    SafeByteArray getAllData()const{return allData;} // der ganze rohdatenschmonsens
    SafeByteArray getPayload();                         // nur alles außer dem Header
    bool transactionFinished()const{return stalled == processed;}
private:
    void processInput(); // headerdaten aus rohdaten basteln
private:
    SafeByteArray allData;          //membervariablen
    quint32 instruction = 0;
    quint32 addressedProgram = 0;
    quint32 arguments = 0;
    quint32 contentLength = 0;
    quint32 stalled = 0;
    quint32 processed = 0;
public: // getter
    quint32 getInstructionCode()const{return instruction;}
    quint32 getAddressedProgram()const{return addressedProgram;}
    quint32 getPassedArguments()const{return arguments;}
    quint32 getContentLength()const{return contentLength;}

    void print() {// ausgabe
        std::cerr << "...Instruction..\nCode: "
        << instruction << "\nProgramm: "
        << addressedProgram << "\narguments: "
        << arguments << "\ncontent: "
        << QString(*getPayload()).toStdString() <<std::endl;
    }
};
}

#undef HEADERSIZE
#endif // INSTRUCTIONHANSZ_H
