include(../defaults.pri)

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TEMPLATE = app

TARGET = mwimagefinder

SOURCES += main.cpp

LIBS += -L../src -lmyapp
LIBS += -L../src/csv -lmwcsv
LIBS += -L../ext -lmwext

#HEADERS +=
