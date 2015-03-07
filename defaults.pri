INCLUDEPATH += $$PWD/src
SRC_DIR = $$PWD


#QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -std=c++1y
QMAKE_CXXFLAGS += -DMAGICKCORE_QUANTUM_DEPTH=16
QMAKE_CXXFLAGS += -DMAGICKCORE_HDRI_ENABLE=false


fedora {
    message("ImageMagick linking paths for Fedora")

    INCLUDEPATH += /usr/include/ImageMagick-6

    unix:!macx: LIBS += -lMagick++-6.Q16
    unix:!macx: LIBS += -lMagickCore-6.Q16
} else {
    message("ImageMagick linking paths for Ubuntu")

    INCLUDEPATH += /usr/include/ImageMagick

    unix:!macx: LIBS += -lMagick++
    unix:!macx: LIBS += -lMagickCore
}

unix:!macx: LIBS += -lboost_system
unix:!macx: LIBS += -lboost_filesystem
unix:!macx: LIBS += -lboost_regex
unix:!macx: LIBS += -lboost_program_options
