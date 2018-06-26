﻿#include <QApplication>
#include <iostream>
#include <QFile>

#include "mainwindow.h"
#include "mongolib.h"

#define TESTFILE "C:/Users/Benedikt/Documents/GitHub/Sefa-11-12/project_folder/testfile.jpg"

#define PORTONE 2222
#define PORTTWO (PORTONE+1)

using Mongo::MngThManager;
using Mongo::MngFileManager;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MngThManager managerOne(PORTONE);
    MngThManager managerTwo(PORTTWO);
    MngFileManager fManagerOne(PORTTWO+1);
    MngFileManager fManagerTwo(PORTTWO+2);
    MainWindow w(&managerTwo,&fManagerTwo);
    w.show();
    managerOne.createConnection(QHostAddress(QHostAddress::LocalHost),PORTTWO);
    //works theoretically, for messages with less payload than 0xFFFF
    srand(time(NULL));
//    for(int i = 0; i < 10; i++){
//        quint16 port = (rand()%65500)+35;
//        QString schtring = QString::number(port); // TODO: add blocking while instruction is sent
//        managerOne.enqueueInstruction(Mongo::Instructions::Chat,0,QByteArray(schtring.toUtf8()));
//    }
    QFile file(TESTFILE);
    if(file.exists()){
        std::cout << "FILE EXISTS\n";
        fManagerOne.createConnection(QHostAddress(QHostAddress::LocalHost),PORTTWO+2);
        fManagerOne.enqueueFile(&file,Mongo::Filetype::Picture);
        std::cout << "Hallelujah\n";
    }
    std::cout << "Main:: " << file.exists() << "\n";
    return a.exec();
}
