#include <instructionhansz.h>
#include <iostream>

#define HEADERSIZE (sizeof(Mongo_Header)+sizeof(Instruction_Header))

extern "C"{
void ChryHexdump(const char *data_buffer, const unsigned int length, FILE *output = stdout){
    fprintf(output,"\nNEW DUMP:\n");
    unsigned char byte;
    unsigned int i, j;
    for (i=0;i < length; i++){
        byte = data_buffer[i];
        fprintf(output,"%02x ",data_buffer[i]);
        if((i%16)==15||(i==length-1)){
            for(j=0;j<15-(i%16);j++)
                fprintf(output,"    ");
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

namespace Mongo {
InstructionHansz::InstructionHansz(quint32 instr, quint32 toPrgm, quint32 args, const QByteArray &payload):
    instruction(instr),addressedProgram(toPrgm), arguments(args),contentLength(payload.size()){
    if(payload.size()>MONGO_INSTRUCTION_MAXIMUM){
        std::cerr << "[ERROR] Payload size exceeds valid maximum\n";
        instr = InvalidInstr;
        return;
    }
    allData = SafeByteArray(new QByteArray());
    Mongo_Header mongo;
    Instruction_Header instructionH;
    memset(&mongo,0,sizeof(mongo));
    memset(&instructionH,0,sizeof(instructionH));

    mongo.mng_type = MONGO_TYPE_INST;
    instructionH.args = arguments;
    instructionH.contLen = contentLength;
    instructionH.exCode = instruction;
    instructionH.prgmSpec = addressedProgram;
    mongo.payload = HEADERSIZE+payload.size();

    allData->append((char*)&mongo,sizeof(Mongo_Header));
    allData->append((char*)&instructionH,sizeof(Instruction_Header));
    allData->append(payload);

    printf("Overall Instruction Size: %i\n",allData->size());
//    printf("OUT:");
//    ChryHexdump((char*)&mongo,sizeof(Mongo_Header));
//    printf("OUT:");
//    ChryHexdump((char*)&instructionH,sizeof(Instruction_Header));
//    ChryHexdump(allData->constData(),allData->size(),stderr);
}
InstructionHansz::InstructionHansz(const SafeByteArray input):
    allData(new QByteArray(*input)){
//    ChryHexdump(allData->constData()+HEADERSIZE,allData->size()-HEADERSIZE);
    processed = input->size();
    processInput();
}
void InstructionHansz::processInput(){
    if(processed >= (sizeof(Mongo_Header)+sizeof(Instruction_Header)) && !instruction){
        Mongo_Header *mongo = (Mongo_Header*)allData->constData();
//        printf("INCOMING: \n");
//        ChryHexdump((char*)mongo,sizeof(Mongo_Header));
        Instruction_Header *inst = (Instruction_Header*)(allData->constData()+sizeof(Mongo_Header));
        printf("INCOMING: \n");
//        ChryHexdump(allData->constData(),allData->size(),stdout);
//        ChryHexdump((char*)inst,sizeof(Instruction_Header));
        instruction = inst->exCode;
        arguments = inst->args;
        addressedProgram = inst->prgmSpec;
        contentLength = inst->contLen;
        stalled = mongo->payload;
    }
}
SafeByteArray InstructionHansz::getPayload(){
//    std::cerr << "HEADERSIZE: " << HEADERSIZE << "\n";
//    std::cerr << "PAYLOADSIZE: " << allData->size()-HEADERSIZE << "\n";
    SafeByteArray array(new QByteArray(allData->constData()+HEADERSIZE,allData->size()-HEADERSIZE));
//    ChryHexdump(array->constData(),array->size());
    return array;
}
}
#undef HEADERSIZE
