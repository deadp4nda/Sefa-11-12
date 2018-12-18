//
// Created by Chrystalkey on 08.12.2018.
//

#include <iostream>
#include "terminal.h"
#include <QScrollBar>

Terminal::Terminal(QWidget *parent) :QWidget(parent){
    input = new TerminalInput(this);
    term = new QTextBrowser(this);
    term->setReadOnly(true);
    term->setTextBackgroundColor(Qt::black);
    term->setTextColor(Qt::white);
    term->setAcceptRichText(true);
    term->setStyleSheet("background-color:black;");
    layout = new QVBoxLayout(this);
    layout->addWidget(term,100);
    layout->addWidget(input);
    setLayout(layout);
    connect(input,&QLineEdit::returnPressed,this,&Terminal::returnPressed);
    term->insertPlainText(">>>");
}

void Terminal::output(QString sometext, QColor col) {
    QString cont = "";
    if(term->toPlainText().count("\n") > 500) {
        cont = term->toPlainText();
        cont = cont.right(cont.indexOf("\n"));
        term->clear();
        term->setText(cont);
    }
    std::cout << cont.toStdString();
    term->setTextColor(col);
    term->insertPlainText("\n>>>" + sometext);
    auto sb = term->verticalScrollBar();
    sb->setValue(sb->maximum());
}

void Terminal::returnPressed() {
    if(input->text()== "")return;
    output(input->text(),Qt::white);
    emit Message(input->text());
    input->clear();
}
