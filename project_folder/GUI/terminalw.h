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
#include <lua.hpp>

#define LPORTO 0x4242 // anweisungsport/ dateiport-1

class TerminalW :public QMainWindow{ // das hauptfenster ist ein hauptfenster
    Q_OBJECT
public:
    enum Source{    // quelle der eingabe, wird auf bestimmte Farbe gemappt
        UserInput,
        LuaOutput,
        CError
    };
    TerminalW(Mango::MngThManager*,Mango::MngFileManager*,lua_State*); // initialisierung: 2 manager und eine Lua-State
    ~TerminalW(); // destruktor
public slots:
    void issueMessage(QString, Source); // schreibe nachricht auf Terminal
    void internMsg(QString);            // callback nur für das Label über dem Terminal
protected:
    void closeEvent(QCloseEvent*);      // aufräumen, wenn das Fenster geschlossen wird
private:
    void setupGUI();                    // self-explanatory?

private slots:
    void Message(QString);              // eine Eingabe vom Nutzer wurde mit Enter bestätigt und geht an die Eingabeverarbeitung in Lua

private:
    QLabel *label = nullptr;                            // unwichtig, implementierungsdetail
    Terminal *terminal = nullptr;                       // terminal+eingabefeld
    QWidget *central = nullptr;                         // unwichtig, implementierungsdetail
    QLabel *files_inq = nullptr;                        // schriftzug über dem Terminal

    QVBoxLayout *vlayout = nullptr,*v2layout = nullptr; // layouts, die machen, dass alles hübsch mitskaliert und so
    QHBoxLayout *hlayout = nullptr;

    Mango::MngFileManager   *fMgr = nullptr;            // die manager. und täglich grüßt das murmeltier
    Mango::MngThManager     *iMgr = nullptr;

    lua_State *L;

    QHostAddress theotherone;                           // unwichtig, implementierungsdetail
    quint16 theotherport;                               // +1
};


#endif //MANGO_TERMINALW_H
