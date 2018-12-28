//
// Created by Chrystalkey on 08.12.2018.
//

#ifndef MANGO_TERMINAL_H
#define MANGO_TERMINAL_H

#include <QWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

class Terminal : public QTextEdit {
    Q_OBJECT
public:
    Terminal(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *) override;
    void mousePressEvent(QMouseEvent *) override{setFocus();}
    void mouseDoubleClickEvent(QMouseEvent* )override{}
    void contextMenuEvent(QContextMenuEvent *) override{}

public slots:
    void output( QString , QColor);
signals:
    void Message( QString );
private:
    QString buffer = "";
    void updateBuffer(){buffer = toPlainText().mid(toPlainText().lastIndexOf("\n>>> ")).remove("\n>>> ");}
};

#endif //MANGO_TERMINAL_H
