//
// Created by Chrystalkey on 08.12.2018.
//

#include <c++/iostream>
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
}

TerminalW::~TerminalW(){
    fMgr->closeIncomingConnection();
    fMgr->closeOutgoingConnection();
    iMgr->closeConnection();
    delete terminal;
    delete startup;
    delete layout;
    delete central;
}

void TerminalW::initialize(QHostAddress adr, quint16 prt) {
    theotherone = adr;
    theotherport = prt;
    fMgr->setConnectionProperties(theotherone,theotherport);
    iMgr->createConnection(adr,prt);
    fMgr->activate();
    startup->hide();
    show();
    std::cerr << QFile::exists("../../../Lua/Main.lua");
    luaL_dofile(L,"../../../Lua/Main.lua");
}

void TerminalW::setupGUI() {
    startup = new StartupWindow(this);
    terminal = new Terminal(this);
    layout = new QVBoxLayout;
    central = new QWidget(this);
    setCentralWidget(central);
    layout->addWidget(terminal);
    central->setLayout(layout);
    connect(terminal,&Terminal::Message,this,&TerminalW::Message);
    connect(startup,&StartupWindow::fuckingBegin,this,&TerminalW::initialize);
    hide();
    startup->show();
}

void TerminalW::issueMessage(QString msg) {
    terminal->output(msg);
}

void TerminalW::Message(QString msg){
    lua_getglobal(L,"interpret_input");
    stackDump(L);
    std::cerr << msg.toStdString() << std::endl;
    lua_pushstring(L, msg.toStdString().c_str());
    int erret = lua_pcall(L,1,0,0);
    if(erret != 0){
        std::cerr << "[ERROR] in TerminalW::Message calling: "<< erret << std::endl;
    }
    lua_settop(L,0);
}