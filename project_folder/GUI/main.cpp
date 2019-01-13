
/* bemerkung: alle c++ klassen sind so aufgebaut, dass in einem Headerfile (*.h) die Methoden und Membervariablen deklariert sind ,und in einem zugehörigen
 * *.cpp - file implementiert. daher sind nur die *.h - dateien kommentiert, um die Funktion der Funktionen zu beschreiben.
 * es gibt nichts, was ich noch dazu sagen könnte. es ist implementiert was dran steht. wirklich.
*/

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
#include <QNetworkInterface>

#include "terminalw.h"

using namespace Mango; // alle funktionen+klassen in globalen namespace eintragen

#define LPORTO 0x4242 // der anweisungsport, und der dateiport -1

extern "C"{// l*** -> Lua-Funktion
static int lIssueInstruction(lua_State *L); // die eine Anweisung verschickt
static int lIssueFile(lua_State *L);        // die eine Datei verschickt
static int lOutputString(lua_State *L);     // die eine Nachricht aufs Terminal schreibt
static int lConnect(lua_State *L);          // die eine verbindung herstellt
static int lDisconnect(lua_State *L);       // die eine verbindung trennt
static int lQuit(lua_State *);              // die das Programm beendet
static int lGetWan(lua_State *);            // die Wan-ip und lokale ip anfordert

// cb -> C-Funktion, die eine Callback-Lua-Funktion aufruft, die...
void cbInstructionIn(SafeInstruction);      // eine hereinkommende Anweisung behandelt
void cbFileInStart(SafeFileHansz);          // eine hereinkommende Dateiübertragung behandelt
void cbFileInComplete();                    // registriert, dass die Übertragung vollständig ist
void cbConnVerification();
void cbError(const QString& error);         // einen Error behandelt
void cbGPFeedback(const QString &msg);      // generelle Meldungen behandelt
void cbConnectionReceived(QHostAddress);    // eine eingehende Verbindung behandelt

// i... / f... einzelne Meldungen, die in einer feedbackfunktion zusammengefasst werden. hässlicher workaround
void iConnInit(){cbGPFeedback("CONNECTION_INITIATED");}
void iConnClsd(){cbGPFeedback("CONNECTION_CLOSED");}
void fFileCanc(){cbGPFeedback("FILE_CANCELLED");}
void fConnClsd(){cbGPFeedback("FILE_CONNECTION_CLOSED");}
void fConnInit(){cbGPFeedback("FILE_CONNECTION_INITIATED");}
void fRemConnRecv(){cbGPFeedback("REMOTE_CONNECTION_RECEIVED");}
void fRemConnClsd(){cbGPFeedback("REMOTE_CONNECTION_CLOSED");cbFileInComplete();}
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
void fFileTransEnded(){cbGPFeedback("TRANSMISSION_ENDED"); cbFileInComplete();}
static void stackDump (lua_State *L) { // hilfsfunktion, lua-stack-dump
    printf("Stackdump:\n");
    int i;
    int top = lua_gettop(L);
    for (i = 1; i <= top; i++) {  /* repeat for each level */
        int t = lua_type(L, i);
        switch (t) {
            case LUA_TSTRING:  /* strings */
                printf("%d '%s'", i, lua_tostring(L, i));
                break;
            case LUA_TBOOLEAN:  /* booleans */
                printf(lua_toboolean(L, i) ? "%d true" : "%d false", i);
                break;
            case LUA_TNUMBER:  /* numbers */
                printf("%d %g", 1, lua_tonumber(L, i));
                break;
            default:  /* other values */
                printf("%d %s", i, lua_typename(L, t));
                break;
        }
        printf("  ");  /* put a separator */
    }
    printf("\n");  /* end the listing */
}
}

TerminalW *wnd = nullptr;           // das Fenster
MngThManager *iMg = nullptr;        // der Anwendungsmanager
MngFileManager *fMg = nullptr;      // der Dateimanager
lua_State *L = nullptr;             // der Lua-state für das Programm
QNetworkAccessManager *manager = new QNetworkAccessManager();// ein qnetworkaccessmanager für die WAN-IP

void connectEverything(MngFileManager*f,MngThManager*i); // verbindung aller signale/slots etc

int main(int argc, char *argv[]){

    L = luaL_newstate(); // Lua initialisierung+ registrierung von Funktionen
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
    lua_setglobal(L,"c_getwan");// siehe oben ende

    std::cerr << QFile::exists("../../../Lua/Main.lua") << std::endl;

    QApplication app(argc,argv); // die anwendung wird beim Betriebssystem registriert

    QFile flubb(QDir::tempPath()+"/pinkkarriertesclownsfischbatallion/file_save.txt");
    flubb.open(QFile::ReadWrite|QFile::Append);
    flubb.close();

    iMg = new MngThManager(LPORTO);         // die Netzwerkmanager werden initialisiert
    fMg = new MngFileManager(LPORTO+1);
    fMg->activate();

    connectEverything(fMg,iMg);

    wnd = new TerminalW(iMg,fMg,L);

    luaL_dofile(L,"Main.lua"); // die main-lua datei wird registriert. ohne die geht gar nix

    cbGPFeedback("TEMP "+QDir::tempPath()+"/pinkkarriertesclownsfischbatallion/"); // registrierung des Temporärordners bei lua

    int ret = app.exec(); // mainloop
    delete iMg;
    delete fMg;
    delete wnd;// aufräumen
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
    const char* payload = lua_tostring(L,3);                     //data
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
    std::cerr << "fmgr: " << fMg->getConnCredentials().toStdString() << "\n";
    std::cerr << "lIssueFile_2\n";
    wnd->internMsg("sdlfkj");
    return 0;
}
int lOutputString(lua_State *L){
    std::cerr << "lOutputString";
    const char *msg = lua_tostring(L,1);
    std::cerr << " " << msg << "\n";
    wnd->issueMessage(QString(msg),TerminalW::LuaOutput);
    return 0;
}
int lConnect(lua_State *L){
    std::cerr << "lConnect\n";
    QString irgendwas = lua_tostring(L,1);
    QHostAddress adr(irgendwas);
    qint16 p = LPORTO;
    if(adr.isNull()){
        wnd->issueMessage("ERROR: invalid IP",TerminalW::CError);
        lua_pushinteger(L,0);
    }else{
        lua_pushinteger(L,iMg->createConnection(adr,p));
        fMg->setConnectionProperties(adr,p+1);
    }
    return 1;
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
            wnd->issueMessage(reply->errorString(),TerminalW::CError);
            lua_pushstring(L, reply->errorString().toLocal8Bit());
        }else {
            lua_pushstring(L, QString(reply->readAll()).toLocal8Bit());
        }
    });
    QNetworkRequest req;
    QUrl forrealnow("https://api.ipify.org");
    req.setUrl(forrealnow);
    manager->get(req);
    timer.start(20000);

    loop.exec();
    timer.stop();

    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol
        && address != QHostAddress(QHostAddress::LocalHost)
        && address.toString().section( ".",-1,-1 ) != "1")
            lua_pushstring(L,address.toString().toUtf8());
    }

    stackDump(L);

    return 2;
}

void cbInstructionIn(SafeInstruction inst) {
    inst->print();
    lua_getglobal(L, "interpret_comm");
    lua_pushinteger(L, inst->getInstructionCode());
    lua_pushinteger(L, inst->getAddressedProgram());
    lua_pushstring(L, *(inst->getPayload()));
    lua_pushinteger(L,inst->getPassedArguments());
    if(lua_pcall(L,4,0,0) != 0){
        wnd->issueMessage("[ERROR] in cbInstructionIn while calling lua\n", TerminalW::CError);
    }
    lua_settop(L,0);
}
void cbFileInStart(SafeFileHansz file){
    lua_getglobal(L,"filetrans_start");
    file->print();
    lua_pushstring(L,file->getName().toLocal8Bit());
    lua_pushstring(L,file->getChecksumString().toLocal8Bit());
    lua_pushinteger(L,file->getFileType());
    lua_pushinteger(L,file->getFileSize());
    if(lua_pcall(L,4,0,0) != 0){
        wnd->issueMessage("[ERROR] in cbFileInStart while calling lua\n", TerminalW::CError);
    }
    lua_settop(L,0);
}
void cbFileInComplete(){
    lua_getglobal(L,"filetrans_end");
    if(lua_pcall(L,0,0,0) != 0){
        wnd->issueMessage("[ERROR] in cbFileInComplete while calling lua\n",TerminalW::CError);
    }
    lua_settop(L,0);
}
void cbConnVerification(){
    lua_getglobal(L,"certificate");
    if(lua_pcall(L,0,0,0) != 0){
        wnd->issueMessage("[ERROR] in cbConnVerification while calling lua\n",TerminalW::CError);
    }
    lua_settop(L,0);
}
void cbError(const QString &error){
    lua_getglobal(L, "error");
    lua_pushstring(L, error.toLocal8Bit());
    if(lua_pcall(L,1,0,0) != 0){
        wnd->issueMessage("[ERROR] in cbError while calling lua with  Message: " + error,TerminalW::CError);
    }
    lua_settop(L,0);
}
void cbGPFeedback(const QString &msg){
    if(msg == "NO_FILES_IN_QUEUE"){ wnd->internMsg("Keine Dateien in der Warteschlange"); return;}
    if(msg.startsWith("BYTES_RECEIVED")) {return;}
    lua_getglobal(L,"feedback");
    lua_pushstring(L, msg.toLocal8Bit());
    stackDump(L);
    if(lua_pcall(L,1,0,0) != 0){
        wnd->issueMessage("[ERROR] in cbGPFeedback while calling lua with Message: " + msg + "\n",TerminalW::CError);
    }
    lua_settop(L,0);
}
void cbConnectionReceived(QHostAddress adr){
    std::cout << "cbConnReceived\n";

    fMg->setConnectionProperties(adr,0x4242+1);

    lua_getglobal(L,"certificate");
    if(lua_pcall(L,0,0,0) != 0){
        wnd->issueMessage("[ERROR] in cbConnectionReceived while calling lua\n",TerminalW::CError);
    }
    lua_settop(L,0);
}
}