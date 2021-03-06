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
    Impl/Vector.cpp \
    main.cpp \
    Impl/ListImpl.cpp \
    Impl/Deque.cpp \
    Impl/hashtable.cpp

HEADERS += \
    TypeTraits.h \
    Iterator.h \
    Allocator.h \
    Construct.h \
    Alloc.h \
    Uninitialize.h \
    Vector.h \
    Algorithm.h \
    Memory.h \
    Utility.h \
    Functional.h \
    Numeric.h \
    String.h \
    Test/permutation_test.h \
    Test/screen_show.h \
    Test/sort_test.h \
    Test/test_copy.h \
    Test/vector_test.h \
    List.h \
    Stack.h \
    Deque.h \
    HashTable.h \
    UnorderedSet.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
