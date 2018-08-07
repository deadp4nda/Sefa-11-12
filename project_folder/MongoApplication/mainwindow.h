#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include "mongolib.h"

using Mongo::MngThManager;
using Mongo::MngFileManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Mongo::MngThManager *,Mongo::MngFileManager*,QWidget *parent = 0);
    ~MainWindow();
public slots:
    void hanszIn(Mongo::SafeInstruction);
    void fileIn(Mongo::SafeFileHansz);
    void connectionRecv();
    void connectionClsd();
    void toggleText();
private:
    QTimer *timer = nullptr;
    QVBoxLayout *layout;
    Mongo::MngThManager *manager;
    Mongo::MngFileManager *fManager;
    quint8 byte = 0;
    QLabel *label = nullptr;
    QLabel *instLabel = nullptr;
    QLabel *fileLabel = nullptr;
};

#endif // MAINWINDOW_H
