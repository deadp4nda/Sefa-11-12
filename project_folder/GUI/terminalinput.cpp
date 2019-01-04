//
// Created by Chrystalkey on 04.01.2019.
//

#include "terminalinput.h"
#include <QLineEdit>
#include <QKeyEvent>

TerminalInput::TerminalInput(QWidget *parent):QLineEdit(parent) {
    QObject::connect(this,&QLineEdit::returnPressed,this,&TerminalInput::onReturn);
    QPalette pal = palette();
    pal.setColor(QPalette::Base, Qt::black);
    pal.setColor(QPalette::Text, Qt::white);
    setPalette(pal);
}

void TerminalInput::onReturn() {
    emit lineIn(text(),Qt::white);
    clear();
    idx=0;
}

void TerminalInput::keyPressEvent(QKeyEvent *event) {
    switch(event->key()){
        case Qt::Key_Up:
            if(idx<s.size()-1) idx++;
            setText(s[idx]);
            break;
        case Qt::Key_Down:
            if(idx>0)idx--;
            setText(s[idx]);
            break;
        default:
            QLineEdit::keyPressEvent(event);
            break;
    }
}