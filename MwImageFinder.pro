TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS = \
    src/csv \
    src \
    app

app.depends = src/csv
app.depends = src

OTHER_FILES += \
    defaults.pri
