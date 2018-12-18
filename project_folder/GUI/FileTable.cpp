//
// Created by THE BERND on 17.12.2018.
//

#include "FileTable.h"
#include <mangolib_global.h>
#include <QTimer>
#include <iostream>

FileTable::~FileTable(){
    timer->stop();
    delete timer;
    csvDB.close();
    delete model;
}

FileTable::FileTable(const QString &fileName) {
    timer = new QTimer;
    timer->setInterval(3000);
    csvDB.setFileName(fileName);
    csvDB.open(QFile::ReadOnly);
    parseFile();
    model = new QStringListModel(modellist);
    setModel(model);
    timer->start();
    //setViewMode(FileTable::ListMode);
}

void FileTable::updateModel() {
    parseFile();
    model->setStringList(modellist);
    QListView::update();
}

//hash;name;type;size
QString unicodeType(QString schlapp){
    switch(schlapp.toInt()){
        case Mango::Audio:
            return "A";
        case Mango::Movie:
            return "M";
        case Mango::Picture:
            return "P";
        case Mango::Text:
            return "T";
        default:
            return " ";
    }
}

void FileTable::parseFile() {
    modellist.clear();
    QStringList all = QString(csvDB.readAll()).split("\n",QString::SkipEmptyParts);
    if(all.isEmpty())
        return;
    for(QString line : all){
        QStringList temp = line.split(",");
        QString rslt = temp[1].length()>20?temp[1].left(17)+"...":temp[1]
                + "   "+ unicodeType(temp[2]);
        modellist.append(rslt);
    }
}

FileTable::FileTable() {
    timer = new QTimer;
    timer->setInterval(3000);
    model = new QStringListModel;
}

void FileTable::setFile(const QString &fileName) {
    csvDB.setFileName(fileName);
    if(!csvDB.open(QFile::ReadOnly)){
        std::cerr << "No Directory file found. now creating a new one\n";
        csvDB.open(QFile::ReadWrite);
        csvDB.close();
        csvDB.open(QFile::ReadOnly);
    }
    timer->start();
    updateModel();
}
