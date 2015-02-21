include(../defaults.pri)

CONFIG   += console

CONFIG   -= app_bundle
CONFIG   -= qt

TEMPLATE = lib

TARGET = mwext

SOURCES += \
    format.cpp

HEADERS += \
    format.h
    infix_iterator.h

