//
// Created by Chrystalkey on 08.12.2018.
//

#include <iostream>
#include <iomanip>
#include "terminalw.h"
#include <lua.hpp>

static void stackDump (lua_State *L) {
    printf("Stackdump:\n");
    int i;
    int top = lua_gettop(L);
    for (i = 1; i <= top; i++) {  /* repeat for each level */
        int t = lua_type(L, i);
        switch (t) {
            case LUA_TSTRING:  /* strings */
                printf("`%s'", lua_tostring(L, i));
                break;
            case LUA_TBOOLEAN:  /* booleans */
                printf(lua_toboolean(L, i) ? "true" : "false");
                break;
            case LUA_TNUMBER:  /* numbers */
                printf("%g", lua_tonumber(L, i));
                break;
            default:  /* other values */
                printf("%s", lua_typename(L, t));
                break;
        }
        printf("  ");  /* put a separator */
    }
    printf("\n");  /* end the listing */
}

TerminalW::TerminalW(Mango::MngThManager*img,Mango::MngFileManager*fmg,lua_State*L):
    iMgr(img),fMgr(fmg),L(L) {
    setupGUI();
	terminal->doc->setFontPointSize(20);
}

TerminalW::~TerminalW(){
    fMgr->closeIncomingConnection();
    fMgr->closeOutgoingConnection();
    iMgr->closeConnection();
    delete terminal;
    //delete label;
    delete files_inq;
    delete vlayout;
    delete v2layout;
    delete hlayout;
    delete central;
}

void TerminalW::setupGUI() {
    vlayout = new QVBoxLayout;
    hlayout = new QHBoxLayout;
    v2layout = new QVBoxLayout;

    files_inq = new QLabel("Keine Dateien in der Warteschlange");
    //label = new QLabel("Files on track");
    terminal = new Terminal(this);
    central = new QWidget(this);
    //fileT = new FileTable;
    //fileT->setFile(QDir::tempPath() + "/pinkkarriertesclownsfischbatallion/file_save.txt");

    setCentralWidget(central);
    //v2layout->addWidget(label);
    //v2layout->addWidget(fileT);
    vlayout->addWidget(files_inq);
    vlayout->addWidget(terminal);
    hlayout->addLayout(vlayout);
    //hlayout->addLayout(v2layout);

    central->setLayout(hlayout);
    connect(terminal,&Terminal::Message,this,&TerminalW::Message);
    show();
	files_inq->hide();
}

void TerminalW::issueMessage(QString msg,Source src) {
    switch(src){
        case UserInput:
            terminal->output(msg,Qt::white);
            break;
        case LuaOutput:
            terminal->output(msg,Qt::green);
            break;
        case CError:
            terminal->output(msg,Qt::red);
            break;
        default:
            terminal->output(msg,Qt::lightGray);
    }
}

void TerminalW::Message(QString msg){
    lua_getglobal(L,"interpret_input");
    stackDump(L);
    std::cerr << msg.toLocal8Bit().data() << std::endl;
    lua_pushstring(L, msg.toLocal8Bit());
    int erret = lua_pcall(L,1,0,0);
    if(erret != 0){
        std::cerr << "[ERROR] in TerminalW::Message calling: "<< erret << std::endl;
    }
    lua_settop(L,0);
}

void TerminalW::internMsg(QString msg) {
    if(msg == "Keine Dateien in der Warteschlange"){
        files_inq->setText("Keine Dateien in der Warteschlange");
    }else{
        files_inq->setText("Es sind Dateien in der Warteschlange");
    }
}

void TerminalW::closeEvent(QCloseEvent *e) {
    lua_getglobal(L,"disconnect");
    lua_pushnil(L);
    int erret = lua_pcall(L,1,0,0);
    if(erret != 0){
        std::cerr << "[ERROR] in TerminalW::closeEvent calling: "<< erret << std::endl;
    }
    lua_settop(L,0);
}