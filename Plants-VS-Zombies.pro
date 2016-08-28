#-------------------------------------------------
#
# Project created by QtCreator 2016-08-28T16:55:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Plants-VS-Zombies
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    globalmanager.cpp

HEADERS  += mainwindow.h \
    globalmanager.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
