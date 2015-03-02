include(../defaults.pri)

CONFIG   += console

CONFIG   -= app_bundle
CONFIG   -= qt

TEMPLATE = lib

TARGET = mwext

SOURCES += \
    format.cpp \
    filesignature.cpp

HEADERS += \
    format.h \    
    infix_iterator.h \
    filesignature.h

