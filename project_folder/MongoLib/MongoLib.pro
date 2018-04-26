#-------------------------------------------------
#
# Project created by QtCreator 2017-12-11T19:52:51
#
#-------------------------------------------------

QT       += network core

QT       -= gui

TARGET = MongoLib
TEMPLATE = lib

DEFINES += MONGOLIB_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += MONGO_LIB

SOURCES += \
    mngserver.cpp \
    datahansz.cpp \
    mngthmanager.cpp \
    mongoconnection.cpp \
    mongofilesocket.cpp \
    instructionhansz.cpp \
    filehansz.cpp

HEADERS += \
        mongolib.h \
        mongolib_global.h \ 
    mngserver.h \
    datahansz.h \
    mngthmanager.h \
    mongoconnection.h \
    mongofilesocket.h \
    instructionhansz.h \
    filehansz.h
