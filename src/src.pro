include(../defaults.pri)

CONFIG   += console

CONFIG   -= app_bundle
CONFIG   -= qt

TEMPLATE = lib

TARGET = myapp

SOURCES += myclass.cpp \
    programoptions.cpp \
    imagefinderoptions.cpp \
    path.cpp

HEADERS += myclass.h \
    infix_iterator.h \
    utils.h \
    programoptions.h \
    imagefinderoptions.h \
    path.h
