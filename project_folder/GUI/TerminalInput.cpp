//
// Created by THE BERND on 14.12.2018.
//

#include "TerminalInput.h"
#include <QKeyEvent>
#include <iostream>

TerminalInput::TerminalInput(QWidget *parent) : QLineEdit(parent) {}

void TerminalInput::keyPressEvent(QKeyEvent *event) {
    QLineEdit::keyPressEvent(event);
    if(anlassfarben.isEmpty())
        return;
    switch(event->key()){
        case Qt::Key_Up:
            if(index != anlassfarben.size()-1) index++;
            setText(anlassfarben[index]);
            break;
        case Qt::Key_Down:
            if(index != 0) index--;
            setText(anlassfarben[index]);
            break;
        case Qt::Key_Return:
        default:
            std::cout << text().toStdString() << std::endl;
            anlassfarben.append(text());
            index = 0;
    }
}
