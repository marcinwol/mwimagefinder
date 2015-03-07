INCLUDEPATH += $$PWD/src
SRC_DIR = $$PWD


#QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -std=c++1y
QMAKE_CXXFLAGS += -DMAGICKCORE_QUANTUM_DEPTH=16
QMAKE_CXXFLAGS += -DMAGICKCORE_HDRI_ENABLE=false

INCLUDEPATH += /usr/include/ImageMagick


#INCLUDEPATH += /opt/boost_1_57_0
#unix:!macx: LIBS += -L/opt/boost_1_57_0/stage/lib



unix:!macx: LIBS += -lMagick++
unix:!macx: LIBS += -lMagickCore

unix:!macx: LIBS += -lboost_system
unix:!macx: LIBS += -lboost_filesystem
unix:!macx: LIBS += -lboost_regex
unix:!macx: LIBS += -lboost_program_options
