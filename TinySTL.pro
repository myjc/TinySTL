#-------------------------------------------------
#
# Project created by QtCreator 2016-09-03T16:20:03
#
#-------------------------------------------------

QT       -= core gui

TARGET = TinySTL
TEMPLATE = lib
CONFIG += staticlib

SOURCES += tinystl.cpp

HEADERS += tinystl.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
