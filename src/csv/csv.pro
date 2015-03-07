include(../../defaults.pri)

CONFIG   += console

CONFIG   -= app_bundle
CONFIG   -= qt
CONFIG   += staticlib

TEMPLATE = lib

TARGET = mwcsv

SOURCES += \ 
	mwcsv.cpp

HEADERS += \ 
	mwcsv.h
