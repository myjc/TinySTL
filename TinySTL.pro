#-------------------------------------------------
#
# Project created by QtCreator 2016-09-03T16:20:03
#
#-------------------------------------------------

QT       -= core gui

TARGET = TinySTL
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    Impl/Alloc.cpp \
    Impl/Vector.cpp

HEADERS += \
    TypeTraits.h \
    Iterator.h \
    Allocator.h \
    Construct.h \
    Alloc.h \
    Uninitialize.h \
    Vector.h \
    Algorithm.h \
    Memory.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
