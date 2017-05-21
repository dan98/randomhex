#-------------------------------------------------
#
# Project created by QtCreator 2017-05-07T10:05:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = randomhex
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    boardwidget.cpp \
    boarditem.cpp \
    board.cpp

HEADERS  += mainwindow.h \
    boardwidget.h \
    boarditem.h \
    board.h

FORMS    += mainwindow.ui
