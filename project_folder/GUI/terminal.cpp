//
// Created by Chrystalkey on 08.12.2018.
//

#include <iostream>
#include "terminal.h"
#include <QScrollBar>
#include <QKeyEvent>

#define repeat(x) for(int i=0;i<x;i++)

Terminal::Terminal(QWidget *parent) :QWidget(parent){
    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::white);
    setPalette(p);
    input = new TerminalInput(this);
    doc = new QTextEdit(this);
    doc->document()->setMaximumBlockCount(420);
    doc->setReadOnly(true);
    connect(input,&TerminalInput::lineIn,this,&Terminal::output);
    connect(input,&TerminalInput::lineIn,this,&Terminal::Message);
    layout = new QVBoxLayout;
    layout->addWidget(doc);
    layout->addWidget(input);
    setLayout(layout);
}

void Terminal::output(QString sometext, QColor col) {
    if(sometext == "Keine Dateien in der Warteschlange") return;
    if(sometext.startsWith("Empfangene Bytes: ") || sometext.startsWith("Gesendete Bytes: "))return;

    auto cur = doc->textCursor();
    cur.movePosition(QTextCursor::End);
    doc->setTextCursor(cur);

    doc->setTextColor(col);
    doc->insertPlainText(sometext+"\n");

    auto sb = doc->verticalScrollBar();
    sb->setValue(sb->maximum());
}