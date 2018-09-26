#include "achim.h"
#include "ui_achim.h"
#include <QLineEdit>
#include <QPushButton>

Achim::Achim(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    Juergen = new QMainWindow(this);
    Juergen->hide();
    QObject::connect(lineEdit,&QLineEdit::returnPressed, this, &Achim::doIt);
    Johannes = new QLabel(widget);
    Johannes->setText("Zum Beispiel");
}

Achim::~Achim()
{
}
void Achim::doIt()
{
    this->hide();
    Juergen->show();
}

void Achim::doSth()
{
}
