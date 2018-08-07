﻿#include <QApplication>
#include <iostream>
#include <QFile>

#include "mainwindow.h"
#include "mongolib.h"

#define TESTFILE "C:/Users/Benedikt/Documents/GitHub/Sefa-11-12/project_folder/testfile.jpg"
#undef TESTFILE
#define TESTFILE "C:/Users/Chrystalkey/Documents/GitHub/Sefa-11-12/project_folder/testfile.jpg"

#define PORTONE 2222
#define PORTTWO 2223

#define PORTTHREE 2224
#define PORTFOUR 2225

using Mongo::MngThManager;
using Mongo::MngFileManager;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MngThManager managerOne(PORTONE);
    MngThManager managerTwo(PORTTWO);
    MngFileManager fManagerOne(PORTTHREE);
    fManagerOne.lockServer();
    fManagerOne.setObjectName("fManagerOne");
    MngFileManager fManagerTwo(PORTFOUR);
    fManagerTwo.setObjectName("fManagerTwo");
    MainWindow w(&managerTwo,&fManagerTwo);
    w.show();
    managerOne.createConnection(QHostAddress(QHostAddress::LocalHost),PORTTWO);
    //works theoretically, for messages with less payload than 0xFFFF
    srand(time(NULL));
    for(int i = 0; i < 10; i++){
        quint16 port = (rand()%65500)+35;
        QString schtring = QString::number(port); // TODO: add blocking while instruction is sent
        managerOne.enqueueInstruction(Mongo::Instructions::Chat,0,QByteArray(schtring.toUtf8()));
    }
    QFile file(TESTFILE);
    if(file.exists()){
        fManagerOne.setConnectionProperties(QHostAddress(QHostAddress::LocalHost),PORTFOUR);
        fManagerOne.enqueueFile(&file,Mongo::Filetype::Picture);
    }
    file.close();
    QDir directory("D:/container/");
    QStringList list = directory.entryList();
    for(QString &str:list){
        file.setFileName(directory.absoluteFilePath(str));
//        Q_ASSERT(file.exists() == true);
        if(file.open(QIODevice::ReadOnly)){
            fManagerOne.enqueueFile(&file,Mongo::Filetype::Undefined);
            file.close();
        }
    }
    return a.exec();
}
