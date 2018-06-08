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

SOURCES += \
    files/filehansz.cpp \
    instructions/instructionhansz.cpp \
    instructions/mngserver.cpp \
    instructions/mngthmanager.cpp \
    instructions/mongoconnection.cpp \
    files/mngfilemanager.cpp \
    files/mngfilesocket.cpp \
    files/mngfileserver.cpp

HEADERS += \
        mongolib.h \
        mongolib_global.h \
    files/filehansz.h \
    instructions/instructionhansz.h \
    instructions/mngserver.h \
    instructions/mngthmanager.h \
    instructions/mongoconnection.h \
    mongolib.h \
    mongolib_global.h \
    files/mngfilemanager.h \
    files/mngfilesocket.h \
    files/mngfileserver.h

DEFINES += MongoLib
