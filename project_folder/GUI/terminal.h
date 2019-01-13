//
// Created by Chrystalkey on 08.12.2018.
//

#ifndef MANGO_TERMINAL_H
#define MANGO_TERMINAL_H

#include <QWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

#include "terminalinput.h"

class Terminal : public QWidget{ // das terminal ist ein widget, und damit einfach in eine Qt-GUI einzubinden
    Q_OBJECT
public:
    Terminal(QWidget *parent = nullptr);
public slots:
    void output( QString , QColor); //  aufruf: schreibe folgendes mit folgender Farbe aufs terminal
signals:
    void Message( QString ); // eine eingabe wird mit enter bestätigt
private:
    TerminalInput *input = nullptr; // Zeileneingabe
    QVBoxLayout *layout = nullptr;  // layout-tool für die richtige ausrichtung
    QTextEdit *doc = nullptr;       // das anzeigende ding
};

#endif //MANGO_TERMINAL_H
