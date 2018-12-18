//
// Created by Chrystalkey on 08.12.2018.
//

#ifndef MANGO_TERMINAL_H
#define MANGO_TERMINAL_H

#include <QWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include "TerminalInput.h"

class Terminal :public QWidget {
    Q_OBJECT
public:
    Terminal(QWidget *parent = nullptr);
public slots:
    void output( QString , QColor);
    void returnPressed();
signals:
    void Message( QString );
private:
    TerminalInput *input = nullptr;
    QTextBrowser *term  = nullptr;
    QVBoxLayout *layout = nullptr;
};

#endif //MANGO_TERMINAL_H
