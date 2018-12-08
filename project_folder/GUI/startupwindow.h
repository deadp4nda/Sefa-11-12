//
// Created by Chrystalkey on 08.12.2018.
//

#ifndef MANGO_STARTUPWINDOW_H
#define MANGO_STARTUPWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QHostAddress>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

class StartupWindow :public QMainWindow {
    Q_OBJECT
public:
    StartupWindow(QWidget *parent = nullptr);
    ~StartupWindow();
signals:
    void fuckingBegin(QHostAddress,quint32);
private slots:
    void pressed();
private:
    QLineEdit *addIn = nullptr;
    QLineEdit *portIn = nullptr;
    QPushButton *start = nullptr;
    QWidget *central = nullptr;
    QVBoxLayout *layout = nullptr;
};


#endif //MANGO_STARTUPWINDOW_H
