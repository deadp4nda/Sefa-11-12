#include "mainwindow.h"
#include <QLabel>
#include <iostream>
#include "instructions/instructionhansz.h"
#include "files/filehansz.h"
#include "files/mngfilemanager.h"

using std::cout;
using std::cerr;
using std::endl;

MainWindow::MainWindow(Mongo::MngThManager *m,Mongo::MngFileManager *fm,QWidget *parent)
    : QMainWindow(parent),manager(m),fManager(fm)
{
    label = new QLabel(this);
    layout = new QVBoxLayout(this);
    timer = new QTimer(this);
    QObject::connect(manager,&Mongo::MngThManager::Message,
                     this,&MainWindow::hanszIn);
    QObject::connect(fManager,&Mongo::MngFileManager::fileReceivingStarted,
                     this,&MainWindow::fileIn);
    QObject::connect(fManager,&Mongo::MngFileManager::remoteConnectionReceived,
                     this,&MainWindow::connectionRecv);
    QObject::connect(timer,&QTimer::timeout,this,&MainWindow::toggleText);
    timer->setInterval(750);
    timer->start();
}
void MainWindow::toggleText(){
    label->setText((QChar)(qrand()%256));
}
void MainWindow::connectionClsd(){
    label->setText("Conn. Closed");
}
void MainWindow::connectionRecv(){
    label->setText("Conn. Recv.");
}
MainWindow::~MainWindow()
{
    delete layout;
}
void MainWindow::hanszIn(Mongo::SafeInstruction hansz){
//    qDebug() <<"Hansz use_count: " << hansz.use_count();
//    qDebug() << "Call: " << ++byte;
//    qDebug() << "Instruction Use_count: " << hansz.use_count();
//    qDebug() << "Code: " << hansz->getInstructionCode();
//    qDebug() << "Prgm: " << hansz->getAddressedProgram();
//    qDebug() << "Args: " << hansz->getPassedArguments();
//    ChryHexdump((char*)hansz->getAllData()->constData(),hansz->getAllData()->size(),stderr);
//    qDebug() << "Length: " << hansz->getPayload()->size();
    label->setText(QString(*hansz->getPayload()));
}

void MainWindow::fileIn(Mongo::SafeFileHansz hansz){
    qDebug() << "File Arrived: " << hansz->getName() << " with Type: " << hansz->getFileType();
}
