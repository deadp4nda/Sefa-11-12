#include "mainwindow.h"
#include "mongolib.h"
#include <QApplication>
#include <iostream>

#define PORTONE 2222
#define PORTTWO (PORTONE+1)

using Mongo::Instructions;
using Mongo::MngThManager;

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
    Mongo::MngThManager managerOne(QDir::tempPath(),PORTONE);
    Mongo::MngThManager managerTwo(QDir::tempPath(),PORTTWO);
    MainWindow w(&managerTwo);
    w.show();
    managerOne.createConnection(QHostAddress(QHostAddress::LocalHost),PORTTWO);
    //works theoretically, for messages with less payload than 0xFFFF
    srand(time(NULL));
    static const quint16 port = (rand()%65500)+35;
    QString schtring = QString::number(port);
    managerOne.sendInstruction(Instructions::Chat,0,QByteArray(schtring.toLocal8Bit()));
    return a.exec();
}
