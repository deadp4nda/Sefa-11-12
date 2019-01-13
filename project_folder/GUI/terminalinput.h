//
// Created by Chrystalkey on 04.01.2019.
//

#ifndef MANGO_TERMINALINPUT_H
#define MANGO_TERMINALINPUT_H

#include <QLineEdit>
#include <QStack>

class TerminalInput :public QLineEdit{ // eingabezeile für das terminal ist ein QLineEdit, also ein widget blahblah leicht einzubinden, macht was es soll
    Q_OBJECT
public:
    TerminalInput(QWidget *parent = nullptr);
    ~TerminalInput();
signals:
    void lineIn(QString,QColor); // eine Nachricht vom Nutzer wird mit enter bestätigt, farbe = weiß
private slots:
    void onReturn(); // triggert lineIn(QString,QColor)

protected:
    void keyPressEvent(QKeyEvent *) override; // überschreibt die Funktion, die bei jeder Eingabe vom System aufgerufen wird
private:
    QList<QString> s; // die liste, in der frühere Eingaben gespeichert werden
    size_t idx = 0; // aktueller index in der liste ^
};


#endif //MANGO_TERMINALINPUT_H
