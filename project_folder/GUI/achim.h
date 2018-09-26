#ifndef ACHIM_H
#define ACHIM_H

#include <QMainWindow>
#include "ui_achim.h"
#include <QLabel>

class Achim : public QMainWindow, private Ui::Achim
{
    Q_OBJECT

public:
    explicit Achim(QWidget *parent = nullptr);
    ~Achim();
public slots:
    void doSth();
    void doIt();
private:
    QLabel* Johannes;
    QMainWindow* Juergen;
};

#endif // ACHIM_H
