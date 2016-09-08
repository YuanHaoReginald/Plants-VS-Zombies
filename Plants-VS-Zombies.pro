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
    globalmanager.cpp \
    welcomewidget.cpp \
    abstractwidget.cpp \
    advencewidget.cpp \
    sun.cpp \
    label.cpp \
    sunmanager.cpp \
    plantcard.cpp \
    cardmanager.cpp \
    abstractplant.cpp \
    sunflower.cpp \
    warmanager.cpp \
    managermanager.cpp \
    wallnut.cpp \
    peashooter.cpp \
    pea.cpp \
    abstractzombies.cpp

HEADERS  += mainwindow.h \
    globalmanager.h \
    abstractwidget.h \
    welcomewidget.h \
    advencewidget.h \
    sun.h \
    label.h \
    sunmanager.h \
    plantcard.h \
    cardmanager.h \
    abstractplant.h \
    sunflower.h \
    warmanager.h \
    enumlist.h \
    managermanager.h \
    wallnut.h \
    peashooter.h \
    pea.h \
    abstractzombies.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
