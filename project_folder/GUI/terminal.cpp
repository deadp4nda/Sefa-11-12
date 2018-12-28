//
// Created by Chrystalkey on 08.12.2018.
//

#include <iostream>
#include "terminal.h"
#include <QScrollBar>
#include <QKeyEvent>

#define repeat(x) for(int i=0;i<x;i++)

Terminal::Terminal(QWidget *parent) :QTextEdit(parent){
    document()->setMaximumBlockCount(420);
    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::white);
    setPalette(p);
}

void Terminal::output(QString sometext, QColor col) {
    if(sometext == "Keine Dateien in der Warteschlange")return;
    if(toPlainText().right(5) == "\n>>> "){
        repeat(5) textCursor().deletePreviousChar();
    }
    setTextColor(col);
    insertPlainText("\n> " + sometext);
    setTextColor(Qt::white);
    insertPlainText("\n>>> ");
    auto sb = verticalScrollBar();
    sb->setValue(sb->maximum());
    updateBuffer();
}

void Terminal::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Left:
        case Qt::Key_Right:
        case Qt::Key_Up:
        case Qt::Key_Down:
            break;
        case Qt::Key_Enter:
        case Qt::Key_Return:
            updateBuffer();
            emit Message(buffer);
            output("",Qt::green);
            break;
        case Qt::Key_Backspace:
        case Qt::Key_Back:
            if(buffer.size() > 0) {
                QTextEdit::keyPressEvent(event);
                updateBuffer();
                break;
            }
            else
                break;
        default:
            setTextColor(Qt::white);
            QTextEdit::keyPressEvent(event);
            buffer = toPlainText().mid(toPlainText().lastIndexOf("\n>>> ")).remove("\n>>> ");
    }
}