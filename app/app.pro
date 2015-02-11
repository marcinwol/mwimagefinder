include(../defaults.pri)

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TEMPLATE = app

SOURCES += main.cpp \
    image.cpp

LIBS += -L../src -lmyapp

HEADERS += \
    image.h
