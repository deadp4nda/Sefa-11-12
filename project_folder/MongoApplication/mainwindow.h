#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include "mongolib.h"

using Mongo::MngThManager;
using Mongo::InstructionHansz;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Mongo::MngThManager *,QWidget *parent = 0);
    ~MainWindow();
public slots:
    void hanszIn(Mongo::SafeInstruction);
    void fileIn(Mongo::SafeFileHansz);
private:
    QVBoxLayout *layout;
    Mongo::MngThManager *manager;
    quint8 byte = 0;
};

#endif // MAINWINDOW_H
