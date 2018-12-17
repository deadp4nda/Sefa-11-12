//
// Created by Chrystalkey on 08.12.2018.
//

#include <iostream>
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
    delete vlayout;
    delete central;
    delete hlayout;
    delete fileT;
}

void TerminalW::setupGUI() {
    terminal = new Terminal(this);
    vlayout = new QVBoxLayout;
    central = new QWidget(this);
    hlayout = new QHBoxLayout;
    fileT = new FileTable;

    setCentralWidget(central);
    vlayout->addWidget(terminal);
    hlayout->addLayout(vlayout);
    hlayout->addWidget(fileT);

    central->setLayout(hlayout);
    connect(terminal,&Terminal::Message,this,&TerminalW::Message);
    show();
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
