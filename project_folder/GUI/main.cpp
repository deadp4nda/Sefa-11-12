#include <QDebug>
#include <QApplication>
#include <Mangolib>
#include <QMainWindow>
#include <iostream>
#include <lua.hpp>

#include <instructions/instructionhansz.h>
#include <files/filehansz.h>
#include <QtNetwork/QNetworkAccessManager>
#include <QNetworkReply>

#include "terminalw.h"

using namespace Mango;

#define LPORTO 0x4242

extern "C"{
static int lIssueInstruction(lua_State *L);
static int lIssueFile(lua_State *L);
static int lOutputString(lua_State *L);
static int lConnect(lua_State *L);
static int lDisconnect(lua_State *L);
static int lQuit(lua_State *);
static int lGetWan(lua_State *);

void cbInstructionIn(SafeInstruction);
void cbFileInStart(SafeFileHansz);
void cbFileInComplete();
void cbConnVerification();
void cbError(const QString& error);
void cbGPFeedback(const QString &msg);
void cbConnectionReceived();

void iConnInit(){cbGPFeedback("CONNECTION_INITIATED");}
void iConnClsd(){cbGPFeedback("CONNECTION_CLOSED");}
void fFileCanc(){cbGPFeedback("FILE_CANCELLED");}
void fConnClsd(){cbGPFeedback("CONNECTION_CLOSED");}
void fConnInit(){cbGPFeedback("CONNECTION_INITIATED");}
void fRemConnRecv(){cbGPFeedback("REMOTE_CONNECTION_RECEIVED");}
void fRemConnClsd(){cbGPFeedback("REMOTE_CONNECTION_CLOSED");}
void fError(MngFileManager::MangolibError mango){
    QString ermsg = "MngFileManager: ";
    switch(mango){
        case MngFileManager::StillFilesToSend:
            cbError(ermsg+"Still files to send");
            break;
        case MngFileManager::NoConnectionToClose:
            cbError(ermsg+"There is no connection to close");
            break;
        case MngFileManager::StillConnected:
            cbError(ermsg+"Still sending a file at closing attempt");
            break;
        case MngFileManager::ConnectionFailed:
            cbError(ermsg+"Failed to establish connection");
            break;
        case MngFileManager::FileInvalid:
            cbError(ermsg+"File is invalid");
            break;
        default:
            cbError(ermsg+"Unknown error");
    }
}

void fJRecv(qint64 recv){cbGPFeedback("BYTES_RECEIVED "+QString::number(recv));}
void fJSent(qint64 sent){cbGPFeedback("BYTES_SENT " + QString::number(sent));}
void fNoFls(){cbGPFeedback("NO_FILES_IN_QUEUE");}
void fFileTransStart(){cbGPFeedback("TRANSMISSION_STARTED");}
void fFileTransEnded(){cbGPFeedback("TRANSMISSION_ENDED");}
}

TerminalW *wnd = nullptr;
MngThManager *iMg = nullptr;
MngFileManager *fMg = nullptr;
lua_State *L = nullptr;
QNetworkAccessManager *manager = new QNetworkAccessManager();

void connectEverything(MngFileManager*f,MngThManager*i);

int main(int argc, char *argv[]){

    L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushcfunction(L,lIssueInstruction);
    lua_setglobal(L,"c_issue_instruction");
    lua_pushcfunction(L,lIssueFile);
    lua_setglobal(L,"c_issue_file");
    lua_pushcfunction(L,lOutputString);
    lua_setglobal(L,"c_terminal_output");
    lua_pushcfunction(L,lConnect);
    lua_setglobal(L,"c_connect_to");
    lua_pushcfunction(L,lDisconnect);
    lua_setglobal(L,"c_disconnect");
    lua_pushcfunction(L,lQuit);
    lua_setglobal(L,"c_squit");
    lua_pushcfunction(L,lGetWan);
    lua_setglobal(L,"c_getwan");

    std::cerr << QFile::exists("../../../Lua/Main.lua") << std::endl;

    QApplication app(argc,argv);

    luaL_dofile(L,"../../../Lua/Main.lua");
    iMg = new MngThManager(LPORTO+1);
    fMg = new MngFileManager(LPORTO);
    connectEverything(fMg,iMg);

    wnd = new TerminalW(iMg,fMg,L);
    int ret = app.exec();
    delete wnd;
    delete iMg;
    delete fMg;
    lua_close(L);
    return ret;
}

void connectEverything(MngFileManager*f,MngThManager*i){
    QObject::connect(i,&MngThManager::Message,                      cbInstructionIn);
    QObject::connect(i,&MngThManager::connectionInitiated,          iConnInit);
    QObject::connect(i,&MngThManager::connectionClosed,             iConnClsd);
    //QObject::connect(i,&MngThManager::connectionInitiated,          cbConnVerification);
    QObject::connect(i,&MngThManager::connectionReceived,           cbConnectionReceived);

    QObject::connect(f,&MngFileManager::fileReceivingStarted,       cbFileInStart);
    QObject::connect(f,&MngFileManager::fileTransmissionStarted,    fFileTransStart);
    QObject::connect(f,&MngFileManager::fileSuccessfulReceived,     cbFileInComplete);
    QObject::connect(f,&MngFileManager::fileTransmissionEnded,      fFileTransEnded);
    QObject::connect(f,&MngFileManager::fileCancelled,              fFileCanc);
    QObject::connect(f,&MngFileManager::connectionClosed,           fConnClsd);
    QObject::connect(f,&MngFileManager::connectionInitiated,        fConnInit);
    QObject::connect(f,&MngFileManager::remoteConnectionReceived,   fRemConnRecv);
    QObject::connect(f,&MngFileManager::remoteConnectionClosed,     fRemConnClsd);
    QObject::connect(f,&MngFileManager::error,                      fError);
    QObject::connect(f,&MngFileManager::noFilesToSend,              fNoFls);
    QObject::connect(f,&MngFileManager::justSent,                   fJSent);
    QObject::connect(f,&MngFileManager::justReceived,               fJRecv);
}

extern "C"{
int lIssueInstruction(lua_State *L){ //
    std::cerr << "lIssueInstruction\n";
    qint32 instr = (quint32)luaL_checkinteger(L,1);             //instruction
    qint32 toPrg = (quint32)luaL_checkinteger(L,2);             //programm
    const char* payload= lua_tostring(L,3);                     //data
    qint32 args  = (quint32)luaL_checkinteger(L,4);             //args

    iMg->enqueueInstruction(instr,toPrg,QByteArray(payload),args);
    return 0;
}
int lIssueFile(lua_State *L){
    std::cerr << "lIssueFile\n";
    const char *fName = lua_tostring(L,1);
    qint64 type = luaL_checkinteger(L,2);
    QFile file(fName);
    file.open(QFile::ReadOnly);
    fMg->enqueueFile(&file,type);
    return 0;
}
int lOutputString(lua_State *L){
    std::cerr << "lOutputString\n";
    const char *msg = lua_tostring(L,1);
    wnd->issueMessage(QString(msg),TerminalW::LuaOutput);
    return 0;
}
int lConnect(lua_State *L){
    std::cerr << "lConnect\n";
    QString irgendwas = lua_tostring(L,1);
    QHostAddress adr(irgendwas);
    qint16 p = (qint16)luaL_checkinteger(L,2);
    p = (qint16)(p ? p : LPORTO);
    if(adr.isNull()){
        wnd->issueMessage("ERROR: invalid IP",TerminalW::CError);
    }else{
        iMg->createConnection(adr,p);
        fMg->setConnectionProperties(adr,p);
    }
    return 0;
}
int lDisconnect(lua_State *){
    std::cerr << "lDisconnect\n";
    iMg->closeConnection();
    fMg->closeOutgoingConnection();
    fMg->closeIncomingConnection();
    return 0;
}

int lQuit(lua_State *){
    std::cerr << "lQuit\n";
    wnd->close();
    return 0;
}

int lGetWan(lua_State *L){
    QTimer timer;
    QEventLoop loop;
    QObject::connect(&timer,&QTimer::timeout,&loop,&QEventLoop::quit);
    QObject::connect(manager, &QNetworkAccessManager::finished,&loop,&QEventLoop::quit);
    QObject::connect(manager, &QNetworkAccessManager::finished,[=](QNetworkReply *reply){
        if(reply->error()){
            std::cerr << reply->errorString().toStdString() << std::endl;
            lua_pushstring(L, reply->errorString().toStdString().c_str());
        }else {
            lua_pushstring(L, QString(reply->readAll()).toStdString().c_str());
        }
    });
    QNetworkRequest req;
    req.setUrl(QUrl("https://api.ipify.org"));
    manager->get(req);
    timer.start(20000);
    loop.exec();
    return 1;
}

void cbInstructionIn(SafeInstruction inst) {
    lua_getglobal(L, "interpret_comm");
    lua_pushinteger(L, inst->getInstructionCode());
    lua_pushinteger(L, inst->getAddressedProgram());
    lua_pushstring(L, inst->getPayload()->data());
    lua_pushinteger(L,inst->getPassedArguments());
    if(lua_pcall(L,4,0,0) != 0){
        std::cerr << "[ERROR] in cbInstructionIn while calling lua\n";
    }
    lua_settop(L,0);
}
void cbFileInStart(SafeFileHansz file){
    lua_getglobal(L,"filetrans_start");
    lua_pushstring(L,file->getName().toStdString().c_str());
    lua_pushstring(L,file->getChecksumString().toStdString().c_str());
    lua_pushinteger(L,file->getFileType());
    lua_pushinteger(L,file->getFileSize());
    if(lua_pcall(L,4,0,0) != 0){
        std::cerr << "[ERROR] in cbFileInStart while calling lua\n";
    }
    lua_settop(L,0);
}
void cbFileInComplete(){
    lua_getglobal(L,"filetrans_end");
    if(lua_pcall(L,0,0,0) != 0){
        std::cerr << "[ERROR] in cbFileInComplete while calling lua\n";
    }
    lua_settop(L,0);
}
void cbConnVerification(){
    lua_getglobal(L,"certificate");
    if(lua_pcall(L,0,0,0) != 0){
        std::cerr << "[ERROR] in cbConnVerification while calling lua\n";
    }
    lua_settop(L,0);
}
void cbError(const QString &error){
    lua_getglobal(L, "error");
    lua_pushstring(L, error.toStdString().c_str());
    std::cerr << error.toStdString() << std::endl;
    if(lua_pcall(L,1,0,0) != 0){
        std::cerr << "[ERROR] in cbError while calling lua\n";
    }
    lua_settop(L,0);
}
void cbGPFeedback(const QString &msg){
    std::cout << msg.toStdString() << std::endl;
    lua_getglobal(L,"feedback");
    lua_pushstring(L, msg.toStdString().c_str());
    lua_pushnil(L);
    if(lua_pcall(L,2,0,0) != 0){
        std::cerr << "[ERROR] in cbGPFeedback while calling lua\n";
    }
    lua_settop(L,0);
}
void cbConnectionReceived(){
    std::cout << "cbConnReceived\n";
    lua_getglobal(L,"certificate");
    if(lua_pcall(L,0,0,0) != 0){
        std::cerr << "[ERROR] in cbConnectionReceived while calling lua\n";
    }
    lua_settop(L,0);
}
}