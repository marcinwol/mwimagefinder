TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS = \
    ext \
    src/csv \
    src \   
    app


app.depends = ext
app.depends = src/csv
app.depends = src

OTHER_FILES += \
    defaults.pri


binary.files += app/mwimagefinder
binary.path = /opt/mwimagefinder
INSTALLS += binary

