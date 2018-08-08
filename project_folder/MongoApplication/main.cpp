#include <QApplication>
#include <iostream>
#include <QFile>
#include <thread>
#include <random>

#include "mainwindow.h"
#include "mongolib.h"

//#define TESTFILE "C:/Users/Benedikt/Documents/GitHub/Sefa-11-12/project_folder/testfile.jpg"
//#undef TESTFILE
//#define TESTFILE "C:/Users/Chrystalkey/Documents/GitHub/Sefa-11-12/project_folder/testfile.jpg"

#define PORTONE 2222
#define PORTTWO 2223

#define PORTTHREE 2224
#define PORTFOUR 2225

using Mongo::MngThManager;
using Mongo::MngFileManager;

Q_DECLARE_METATYPE(Mongo::SafeFileHansz)

MngThManager *managerOne, *managerTwo;
MngFileManager *fManagerOne, *fManagerTwo;

int main(int argc, char *argv[])
{
    qRegisterMetaType<Mongo::SafeFileHansz>("Mongo::SafeFileHansz");
    qDebug() << "Full ones: " << byteArrayToBase32(QByteArray(32,(char)0xFF));
    QApplication a(argc, argv);
    managerOne = new MngThManager(PORTONE);
    managerTwo = new MngThManager(PORTTWO);
    fManagerOne = new MngFileManager(PORTTHREE);
    fManagerOne->lockServer();
    fManagerOne->setObjectName("fManagerOne");
    fManagerTwo = new MngFileManager(PORTFOUR);
    fManagerTwo->setObjectName("fManagerTwo");
    MainWindow w(managerTwo,fManagerTwo,fManagerOne);

    w.show();
    managerOne->createConnection(QHostAddress(QHostAddress::LocalHost),PORTTWO);
    srand(time(NULL));
    for(int i = 0; i < 10; i++){
        quint16 port = (rand() % 65000)+535;
        QString schtring = QString::number(port);
        managerOne->enqueueInstruction(Mongo::Instructions::Chat,0,QByteArray(schtring.toUtf8()));
    }

    fManagerOne->activate();
    fManagerTwo->activate();

    int returnValue = a.exec();
    delete managerOne;
    delete managerTwo;
    delete fManagerOne;
    delete fManagerTwo;
    return returnValue;
}
