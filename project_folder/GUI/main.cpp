#include <QDebug>
#include <QApplication>
#include <Mangolib>
#include <QMainWindow>
#include <iostream>
#include <lua.hpp>

#include <instructions/instructionhansz.h>
#include <files/filehansz.h>

#include "terminalw.h"

using namespace Mango;

extern "C"{
static int lIssueInstruction(lua_State *L);
static int lIssueFile(lua_State *L);
static int lOutputString(lua_State *L);
static int lConnect(lua_State *L);
static int lDisconnect(lua_State *L);
void cbInstructionIn(SafeInstruction);
void cbFileInStart(SafeFileHansz);
void cbFileInComplete();
void cbConnVerification();
void cbError(const QString& error);
}

TerminalW *wnd = nullptr;
MngThManager *iMg = nullptr;
MngFileManager *fMg = nullptr;
lua_State *L = nullptr;

int main(int argc, char *argv[]){

    L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushcfunction(L,lIssueInstruction);
    lua_setglobal(L,"issue_instruction");
    lua_pushcfunction(L,lIssueFile);
    lua_setglobal(L,"issue_file");
    lua_pushcfunction(L,lOutputString);
    lua_setglobal(L,"terminal_output");
    lua_pushcfunction(L,lConnect);
    lua_setglobal(L,"connect_to");
    lua_pushcfunction(L,lDisconnect);
    lua_setglobal(L,"disconnect");

    QApplication app(argc,argv);
    fMg = new MngFileManager(LPORTO);
    QObject::connect(iMg,&MngThManager::Message,cbInstructionIn);
    iMg = new MngThManager(LPORTO+1);
    QObject::connect(fMg,&MngFileManager::fileReceivingStarted,cbFileInStart);
    QObject::connect(fMg,&MngFileManager::fileSuccessfulReceived,cbFileInComplete);
    QObject::connect(iMg,&MngThManager::connectionInitiated,cbConnVerification);
    wnd = new TerminalW(iMg,fMg,L);
    //lua_dofile(L,"main.lua");
    int ret =app.exec();
    delete wnd;
    delete iMg;
    delete fMg;
    return ret;
}

extern "C"{
int lIssueInstruction(lua_State *L){ //
    quint32 instr = (quint32)luaL_checkinteger(L,1);             //instruction
    quint32 toPrg = (quint32)luaL_checkinteger(L,2);             //programm
    const char* payload= lua_tostring(L,3);             //data
    quint32 args  = (quint32)luaL_checkinteger(L,4);             //args

    iMg->enqueueInstruction(instr,toPrg,QByteArray(payload),args);
    return 0;
}
int lIssueFile(lua_State *L){
    const char *fName = lua_tostring(L,1);
    quint64 type = luaL_checkinteger(L,2);
    QFile file(fName);
    file.open(QFile::ReadOnly);
    fMg->enqueueFile(&file,type);
    return 0;
}
int lOutputString(lua_State *L){
    const char *msg = lua_tostring(L,1);
    wnd->issueMessage(msg);
    return 0;
}
int lConnect(lua_State *L){
    QHostAddress adr(QString(lua_tostring(L,1)));
    quint32 p = luaL_checkinteger(L,2);
    if(adr.isNull()){
        wnd->issueMessage("ERROR: invalid IP");
    }else{
        iMg->createConnection(adr,p);
        fMg->setConnectionProperties(adr,p);
    }
    return 0;
}
int lDisconnect(lua_State *){
    iMg->closeConnection();
    fMg->closeOutgoingConnection();
    fMg->closeIncomingConnection();
    return 0;
}
void cbInstructionIn(SafeInstruction inst) {
    lua_getglobal(L, "...");
    lua_pushinteger(L, inst->getInstructionCode());
    lua_pushinteger(L, inst->getAddressedProgram());
    lua_pushstring(L, inst->getPayload()->data());
    lua_pushinteger(L,inst->getPassedArguments());
    if(lua_pcall(L,4,0,0) != 0){
        std::cerr << "[ERROR] in cbInstructionIn while calling lua\n";
    }
}
void cbFileInStart(SafeFileHansz file){
    lua_getglobal(L,"...");
    lua_pushstring(L,file->getChecksumString().toStdString().c_str());
    lua_pushinteger(L,file->getFileType());
    if(lua_pcall(L,2,0,0) != 0){
        std::cerr << "[ERROR] in cbFileInStart while calling lua\n";
    }
}
void cbFileInComplete(){
    lua_getglobal(L,"...");
    if(lua_pcall(L,0,0,0) != 0){
        std::cerr << "[ERROR] in cbFileInComplete while calling lua\n";
    }
}
void cbConnVerification(){
    lua_getglobal(L,"...");
    if(lua_pcall(L,0,0,0) != 0){
        std::cerr << "[ERROR] in cbConnVerification while calling lua\n";
    }
}
}