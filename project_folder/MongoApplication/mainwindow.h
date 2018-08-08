#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mongolib.h"

using Mongo::MngThManager;
using Mongo::MngFileManager;

class QLabel;
class QVBoxLayout;
class QWidget;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Mongo::MngThManager *,Mongo::MngFileManager*,Mongo::MngFileManager*,QWidget *parent = 0);
    ~MainWindow();
signals:
    void aboutToClose();
public slots:
    void hanszIn(Mongo::SafeInstruction);
    void fileIn(Mongo::SafeFileHansz);
    void connectionRecv();
    void connectionClsd();
    void toggleText();

    void sendNextFile();
    void updateFileSize(qint64);
private:
    QTimer *timer = nullptr;
    QVBoxLayout *layout = nullptr;
    Mongo::MngThManager *manager = nullptr;
    Mongo::MngFileManager *fManager = nullptr;
    Mongo::MngFileManager *fManagerForSending = nullptr;
    quint8 byte = 0;
    QWidget *centraal = nullptr;
    QLabel *label = nullptr;
    QLabel *instLabel = nullptr;
    QLabel *fileLabel = nullptr;
    QPushButton *button = nullptr;
    qint64 lastFilesSize = 0;
    qint64 received = 0;
    QString lastFileString;
};

#endif // MAINWINDOW_H
