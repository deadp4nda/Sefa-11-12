//
// Created by THE BERND on 14.12.2018.
//

#ifndef MANGO_TERMINALINPUT_H
#define MANGO_TERMINALINPUT_H

#include <QLineEdit>
#include <QStringList>

class TerminalInput :public QLineEdit{
    Q_OBJECT
public:
    TerminalInput(QWidget* parent);
protected:
    void keyPressEvent(QKeyEvent *);
private:
    QStringList anlassfarben;
    size_t index = 0;
};


#endif //MANGO_TERMINALINPUT_H
