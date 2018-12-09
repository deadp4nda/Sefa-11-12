#include "mainwindow.h"

#include <QLabel>
#include <QVBoxLayout>
#include <iostream>
#include <QPushButton>

#include "instructions/instructionhansz.h"
#include "files/filehansz.h"
#include "files/mngfilemanager.h"

#define TESTFILE "C:/Users/Benedikt/Documents/GitHub/Sefa-11-12/project_folder/testfile.jpg"
#undef TESTFILE
#define TESTFILE "C:/Users/Chrystalkey/Documents/GitHub/Sefa-11-12/project_folder/testfile.jpg"

#define PORTFOUR 2225

using std::cout;
using std::cerr;
using std::endl;

MainWindow::MainWindow(Mongo::MngThManager *m,Mongo::MngFileManager *fm,
                       Mongo::MngFileManager *fmfS,QWidget *parent)
    : QMainWindow(parent),manager(m),fManager(fm),fManagerForSending(fmfS)
{
    setWindowTitle("Mongo Application");
    layout = new QVBoxLayout(this);

    centraal = new QWidget(this);
    label = new QLabel(centraal);
    instLabel = new QLabel(centraal);
    fileLabel = new QLabel(centraal);
    button = new QPushButton("Send Next File",centraal);

    layout->addWidget(label);
    layout->addWidget(instLabel);
    layout->addWidget(button);
    layout->addWidget(fileLabel);

    centraal->setLayout(layout);

    setCentralWidget(centraal);
    timer = new QTimer(this);

    QObject::connect(manager,&Mongo::MngThManager::Message,
                     this,&MainWindow::hanszIn);
    QObject::connect(fManager,&Mongo::MngFileManager::fileReceivingStarted,
                     this,&MainWindow::fileIn);
    QObject::connect(fManager,&Mongo::MngFileManager::remoteConnectionReceived,
                     this,&MainWindow::connectionRecv);
    QObject::connect(timer,&QTimer::timeout,this,&MainWindow::toggleText);
    QObject::connect(button, &QPushButton::pressed,
                     this, &MainWindow::sendNextFile);
    QObject::connect(fManager,&MngFileManager::justReceived,
                     this, &MainWindow::updateFileSize);
    timer->setInterval(750);
    timer->start();
}
void MainWindow::sendNextFile(){
    QFile file(TESTFILE);
    if(file.exists()){
        fManagerForSending->setConnectionProperties(QHostAddress(QHostAddress::LocalHost),PORTFOUR);
        fManagerForSending->enqueueFile(&file,Mongo::Filetype::Picture);
    }
    file.close();
    QDir directory("D:/container/");
    QStringList list = directory.entryList();
    for(QString &str:list){
        file.setFileName(directory.absoluteFilePath(str));
//        Q_ASSERT(file.exists() == true);
        if(file.open(QIODevice::ReadOnly)){
            fManagerForSending->enqueueFile(&file,Mongo::Filetype::Undefined);
            file.close();
        }
    }
}
void MainWindow::toggleText(){
    label->setText((QChar)(qrand()%256));
}
void MainWindow::connectionClsd(){
    //fileLabel->setText("Conn. Closed");
}
void MainWindow::connectionRecv(){
    //fileLabel->setText("Conn. Recv.");
}
MainWindow::~MainWindow()
{
    emit aboutToClose();
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
    instLabel->setText(QString(*hansz->getPayload()));
}

void MainWindow::updateFileSize(qint64 size){
    received += size;
    fileLabel->setText(lastFileString + " Received: " + QString::number(received/1024) +
                       " from " + QString::number(lastFilesSize/1024) +
                       " (" + QString::number( ((double)received/(double)lastFilesSize) *100 ) + "%)");
}
void MainWindow::fileIn(Mongo::SafeFileHansz hansz){
    lastFileString = ("File Arrived: " + hansz->getName() +
                       " with Type: " + QString::number(hansz->getFileType()));
    lastFilesSize = hansz->getFileSize();
    received = 0;
    fileLabel->setText(lastFileString);
}
