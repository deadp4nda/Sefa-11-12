#include "mainwindow.h"
#include "mongolib.h"
#include <QApplication>
#include <iostream>
#include <QFile>
#include <windows.h>

#define PORTONE 2222
#define PORTTWO (PORTONE+1)

using Mongo::Instructions;
using Mongo::MngThManager;
using Mongo::Filetype;

QString operator*(const QString& string, quint32 multiple){
    QString str;
    for(quint32 i = 0; i < multiple;i++){
        str+=string;
    }
    return str;
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mongo::MngThManager managerOne(PORTONE);
    Mongo::MngThManager managerTwo(PORTTWO);
    Mongo::MngFileManager fManagerOne(PORTTWO+1);
    Mongo::MngFileManager fManagerTwo(PORTTWO+2);
    MainWindow w(&managerTwo);
    w.show();
    managerOne.createConnection(QHostAddress(QHostAddress::LocalHost),PORTTWO);
    //works theoretically, for messages with less payload than 0xFFFF
    srand(time(NULL));
    for(int i = 0; i < 10; i++){
        quint16 port = (rand()%65500)+35;
        QString schtring = QString::number(port); // TODO: add blocking while instruction is sent
        managerOne.enqueueInstruction(Instructions::Chat,0,QByteArray(schtring.toLocal8Bit()));
    }
    QFile file("C:/Users/Benedikt/Documents/GitHub/Sefa-11-12/project_folder/testfile.jpg");
//    std::cout << "Main:: " << file.exists() << "\n";
    return a.exec();
}
