# -------------------------------------------------
# Project created by QtCreator 2009-06-26T18:08:01
# -------------------------------------------------
QT += core gui opengl
TARGET = paddles
TEMPLATE = app
SOURCES += main.cpp \
    game.cpp \
    ball.cpp \
    mainwindow.cpp
HEADERS += game.h \
    ball.h \
    opts.h \
    mainwindow.h
FORMS += mainwindow.ui
QMAKE_CXXFLAGS += -std=c++11
