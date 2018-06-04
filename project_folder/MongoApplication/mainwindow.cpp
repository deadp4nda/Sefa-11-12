#include "mainwindow.h"
#include <QLabel>
#include <iostream>
#include "instructions/instructionhansz.h"
#include "files/filehansz.h"
using std::cout;
using std::cerr;
using std::endl;

extern "C"{
void ChryHexdump(const char *data_buffer, const unsigned int length, FILE *output = stdout){
    fprintf(output,"\nNEW DUMP:\n");
    unsigned char byte;
    unsigned int i, j;
    for (i=0;i < length; i++){
        byte = data_buffer[i];
        fprintf(output,"%02x ",data_buffer[i]);
        if((i%16)==15||(i==length-1)){
            for(j=0;j<15-(i%16);j++)
                fprintf(output,"    ");
            fprintf(output,"| ");
            for(j=(i-(i%16));j<=i;j++){
                byte = data_buffer[j];
                if((byte>31)&& (byte <127))
                fprintf(output,"%c",byte);
                else
                    fprintf(output,".");
            }
            fprintf(output,"\n");
        }
    }
}
}

MainWindow::MainWindow(Mongo::MngThManager *m,QWidget *parent)
    : QMainWindow(parent),manager(m)
{
    layout = new QVBoxLayout(this);
    QObject::connect(manager,&Mongo::MngThManager::Message,this,&MainWindow::hanszIn);
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
    QLabel *label = new QLabel(QString(*hansz->getPayload()),this);
    layout->addWidget(label);
    label->show();
}

void MainWindow::fileIn(Mongo::SafeFileHansz hansz){
    qDebug() << "File Arrived: " << hansz->getName() << " with Type: " << hansz->getFileType();
}
