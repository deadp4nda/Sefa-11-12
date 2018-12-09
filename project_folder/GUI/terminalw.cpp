//
// Created by Chrystalkey on 08.12.2018.
//

#include <c++/iostream>
#include "terminalw.h"

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
    startup->hide();
    show();
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
    lua_getglobal(L,"cbTermIn");
    lua_pushstring(L,msg.toStdString().c_str());
    if(lua_pcall(L,1,0,0) != 0){
        std::cerr << "[ERROR] in TerminalW::Message calling" << std::endl;
    }
}