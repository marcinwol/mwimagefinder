include(../defaults.pri)

CONFIG   += console

CONFIG   -= app_bundle
CONFIG   -= qt
CONFIG += staticlib


TEMPLATE = lib

TARGET = mwapp

SOURCES += myclass.cpp \
    programoptions.cpp \
    imagefinderoptions.cpp \
    mwpath.cpp \
    mwimage.cpp \
    utils.cpp \
    mwresolution.cpp

HEADERS += myclass.h \
    utils.h \
    programoptions.h \
    imagefinderoptions.h \
    mwpath.h \
    mwimage.h \
    mwresolution.h
