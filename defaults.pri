INCLUDEPATH += $$PWD/src
SRC_DIR = $$PWD


QMAKE_CXXFLAGS += -std=c++14



INCLUDEPATH += /usr/include/ImageMagick
INCLUDEPATH += /home/m/Downloads/boost_1_57_0
unix:!macx: LIBS += -L/home/m/Downloads/boost_1_57_0/stage/lib


unix:!macx: LIBS += -lMagick++
unix:!macx: LIBS += -lMagickCore

unix:!macx: LIBS += -lboost_system
unix:!macx: LIBS += -lboost_filesystem
unix:!macx: LIBS += -lboost_program_options
