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

class Terminal : public QWidget{
    Q_OBJECT
public:
    Terminal(QWidget *parent = nullptr);
public slots:
    void output( QString , QColor);
signals:
    void Message( QString );
private:
    TerminalInput *input = nullptr;
    QVBoxLayout *layout = nullptr;
    QTextEdit *doc = nullptr;
};

#endif //MANGO_TERMINAL_H
