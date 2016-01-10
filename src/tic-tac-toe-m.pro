#-------------------------------------------------
#
# Project created by QtCreator 2016-01-04T15:07:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tic-tac-toe-m
TEMPLATE = app

CONFIG += C++11


SOURCES += main.cpp\
    gamewizard.cpp \
    gamewindow.cpp \
    board.cpp \
    gamebot.cpp

HEADERS  += \
    gamewizard.h \
    gamewindow.h \
    board.h \
    gamebot.h

FORMS    += \
    gamewizard.ui \
    gamewindow.ui
