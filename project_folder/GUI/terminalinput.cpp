//
// Created by Chrystalkey on 04.01.2019.
//

#include "terminalinput.h"
#include <QLineEdit>
#include <QKeyEvent>
#include <QtCore/QDir>

TerminalInput::TerminalInput(QWidget *parent):QLineEdit(parent) {
    if(QFile::exists(QDir::tempPath()+"/pinkkarriertesclownsfischbatallion/blechschaden.msdga")){
        QFile f(QDir::tempPath()+"/pinkkarriertesclownsfischbatallion/blechschaden.msdga");
        s = QString(f.readAll()).split("\n",QString::SkipEmptyParts);
        f.close();
    }
    QObject::connect(this,&QLineEdit::returnPressed,this,&TerminalInput::onReturn);
    QPalette pal = palette();
    pal.setColor(QPalette::Base, Qt::black);
    pal.setColor(QPalette::Text, Qt::white);
    setPalette(pal);
}

TerminalInput::~TerminalInput() {
    QFile f(QDir::tempPath()+"/pinkkarriertesclownsfischbatallion/blechschaden.msdga");
    for(QString &ss:s){
        if(ss != "") f.write((ss+"\n").toUtf8());
    }
    f.close();
}

void TerminalInput::onReturn() {
    if(text()=="")return;
    emit lineIn(text(),Qt::white);
    s.removeAt(0);
    s.prepend(text());
    s.prepend("");
    clear();
    idx=0;
}

void TerminalInput::keyPressEvent(QKeyEvent *event) {
    switch(event->key()){
        case Qt::Key_Up:
            if(s.size()==0)return;
            if(idx<s.size()-1) idx++;
            setText(s[idx]);
            break;
        case Qt::Key_Down:
            if(s.size()==0)return;
            if(idx>0)idx--;
            setText(s[idx]);
            break;
        default:
            QLineEdit::keyPressEvent(event);
            break;
    }
}