#-------------------------------------------------
#
# Project created by QtCreator 2015-08-06T19:23:58
#
#-------------------------------------------------

QT       += core gui

TARGET = oscilloscope
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    h5fileanalyzer.cpp

HEADERS  += mainwindow.h \
    h5fileanalyzer.h

FORMS    += mainwindow.ui

QMAKE_CXX = h5c++
QMAKE_CXXFLAGS += -std=c++11
QMAKE_LINK = h5c++

OTHER_FILES += \
    ../out.h5
