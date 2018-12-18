//
// Created by Chrystalkey on 08.12.2018.
//

#ifndef MANGO_TERMINALW_H
#define MANGO_TERMINALW_H
#include <QMainWindow>
#include <QtNetwork/QHostAddress>
#include <QLabel>

#include <Mangolib>

#include "terminal.h"
#include "FileTable.h"
#include <lua.hpp>

#define LPORTO 0x4242

class TerminalW :public QMainWindow{
    Q_OBJECT
public:
    TerminalW(Mango::MngThManager*,Mango::MngFileManager*,lua_State*);
    ~TerminalW();
public slots:
    void issueMessage(QString);
private:
    void setupGUI();
private slots:
    void Message(QString);

private:
    Terminal *terminal = nullptr;
    QWidget *central = nullptr;
    FileTable *fileT = nullptr;
    QLabel *label = nullptr;

    QVBoxLayout *vlayout = nullptr,*v2layout = nullptr;
    QHBoxLayout *hlayout = nullptr;

    Mango::MngFileManager   *fMgr = nullptr;
    Mango::MngThManager     *iMgr = nullptr;

    lua_State *L;

    QHostAddress theotherone;
    quint16 theotherport;
};


#endif //MANGO_TERMINALW_H
