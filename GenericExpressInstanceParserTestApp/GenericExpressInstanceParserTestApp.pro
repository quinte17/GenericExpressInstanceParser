#-------------------------------------------------
#
# Project created by QtCreator 2014-11-12T19:26:30
#
#-------------------------------------------------

QT       += core testlib

QT       -= gui

TARGET = GenericExpressInstanceParserTestApp
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

TEMPLATE = app
CONFIG(debug, debug|release) {
    DESTDIR = ../debug/bin
    #OBJECTS_DIR = ../debug/objects
}

CONFIG(release, debug|release) {
    DESTDIR = ../release/bin
    #OBJECTS_DIR = ../release/objects
}

SOURCES += main.cpp

OTHER_FILES += \
    example_instances_01.txt

#include
INCLUDEPATH = "../GenericExpressInstanceParser"

#link
unix:LIBS += \
    -L "$$DESTDIR" -lGenericExpressInstanceParser \
    -lfl

#add the bin path to find the GenericExpressInstanceParser lib
release:QMAKE_RPATHDIR += $$DESTDIR

DEFINES += SRCDIR=\\\"$$PWD/\\\"
