//
// Created by Chrystalkey on 08.12.2018.
//

#include "startupwindow.h"

StartupWindow::StartupWindow(QWidget *parent) : QMainWindow(parent){
    addIn = new QLineEdit("IP(v6/v4)",this);
    portIn = new QLineEdit("Optional",this);
    start = new QPushButton("Start",this);
    central = new QWidget(this);
    layout = new QVBoxLayout;
    layout->addWidget(addIn);
    layout->addWidget(portIn);
    layout->addWidget(start);
    setCentralWidget(central);
    central->setLayout(layout);
    connect(start,&QPushButton::pressed,this,&StartupWindow::pressed);
}

StartupWindow::~StartupWindow() {
    delete addIn;
    delete portIn;
    delete start;
    delete layout;
    delete central;
    delete layout;
}

void StartupWindow::pressed() {
    emit fuckingBegin(QHostAddress(addIn->text()),(quint32)portIn->text().toUInt());
}
