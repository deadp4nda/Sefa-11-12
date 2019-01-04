//
// Created by Chrystalkey on 04.01.2019.
//

#ifndef MANGO_TERMINALINPUT_H
#define MANGO_TERMINALINPUT_H

#include <QLineEdit>
#include <QStack>

class TerminalInput :public QLineEdit{
    Q_OBJECT
public:
    TerminalInput(QWidget *parent = nullptr);
signals:
    void lineIn(QString,QColor);
private slots:
    void onReturn();

protected:
    void keyPressEvent(QKeyEvent *) override;
private:
    QStack<QString> s;
    size_t idx = 0;
};


#endif //MANGO_TERMINALINPUT_H
