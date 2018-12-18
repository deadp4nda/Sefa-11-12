//
// Created by THE BERND on 17.12.2018.
//

#ifndef MANGO_FILETABLE_H
#define MANGO_FILETABLE_H

#include <QListView>
#include <QFile>
#include <QStringListModel>

class QTimer;

class FileTable :public QListView {
    Q_OBJECT
public:
    FileTable(const QString &fileName);
    FileTable();
    ~FileTable();
    void setFile(const QString& fileName);
public slots:
    void updateModel();

private:
    QFile csvDB;
    QStringListModel *model;
    QStringList modellist;
    QTimer *timer;
    void parseFile();
};


#endif //MANGO_FILETABLE_H
