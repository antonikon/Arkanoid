#-------------------------------------------------
#
# Project created by QtCreator 2012-12-13T18:02:30
#
#-------------------------------------------------

QT       += core gui phonon

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Arkanoid1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    player.cpp \
    world.cpp \
    ball.cpp \
    block.cpp

HEADERS  += mainwindow.h \
    player.h \
    world.h \
    ball.h \
    block.h \
    values.h

FORMS    += mainwindow.ui

LIBS += -lBox2D
