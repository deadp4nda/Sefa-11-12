#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include "mongolib.h"

using Mongo::MngThManager;
using Mongo::InstructionHansz;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Mongo::MngThManager *,Mongo::MngFileManager*,QWidget *parent = 0);
    ~MainWindow();
public slots:
    void hanszIn(Mongo::SafeInstruction);
    void fileIn(Mongo::SafeFileHansz);
private:
    QVBoxLayout *layout;
    Mongo::MngThManager *manager;
    Mongo::MngFileManager *fManager;
    quint8 byte = 0;
    QLabel *label = nullptr;
};

#endif // MAINWINDOW_H
