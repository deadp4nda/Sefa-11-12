#include "instructionhansz.h"
#include <iostream>

#define HEADERSIZE (sizeof(Mongo_Header)+sizeof(Instruction_Header))

namespace Mango {
InstructionHansz::InstructionHansz(quint32 instr, quint32 toPrgm, quint32 args, const QByteArray &payload):
    instruction(instr),addressedProgram(toPrgm), arguments(args),contentLength(payload.size()){
    if(payload.size()>MANGO_INSTRUCTION_MAXIMUM){
        std::cerr << "[ERROR] Payload size exceeds valid maximum\n";
        instr = InvalidInstr;
        return;
    }
    allData = SafeByteArray(new QByteArray());
    Mongo_Header mongo;
    Instruction_Header instructionH;
    memset(&mongo,0,sizeof(mongo));
    memset(&instructionH,0,sizeof(instructionH));

    mongo.mng_type = MANGO_TYPE_INST;
    instructionH.args = arguments;
    instructionH.contLen = contentLength;
    instructionH.exCode = instruction;
    instructionH.prgmSpec = addressedProgram;
    mongo.payload = HEADERSIZE+payload.size();

    allData->append((char*)&mongo,sizeof(Mongo_Header));
    allData->append((char*)&instructionH,sizeof(Instruction_Header));
    allData->append(payload);
}
InstructionHansz::InstructionHansz(const SafeByteArray input):
    allData(new QByteArray(*input)){
    processed = input->size();
    processInput();
}
void InstructionHansz::processInput(){
    if(processed >= (sizeof(Mongo_Header)+sizeof(Instruction_Header)) && !instruction){
        Mongo_Header *mongo = (Mongo_Header*)allData->constData();
        Instruction_Header *inst = (Instruction_Header*)(allData->constData()+sizeof(Mongo_Header));
        instruction = inst->exCode;
        arguments = inst->args;
        addressedProgram = inst->prgmSpec;
        contentLength = inst->contLen;
        stalled = mongo->payload;
    }
}
SafeByteArray InstructionHansz::getPayload(){
    SafeByteArray array(new QByteArray(allData->constData()+HEADERSIZE,allData->size()-HEADERSIZE));
    return array;
}
}
#undef HEADERSIZE
