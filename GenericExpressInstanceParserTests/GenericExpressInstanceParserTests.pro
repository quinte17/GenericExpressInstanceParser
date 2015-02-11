#-------------------------------------------------
#
# Project created by QtCreator 2014-11-23T11:02:19
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = GenericExpressInstanceParserTests
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

TEMPLATE = app
CONFIG(debug, debug|release) {
    DESTDIR = ../debug/bin
   # OBJECTS_DIR = ../debug/objects
}

CONFIG(release, debug|release) {
    DESTDIR = ../release/bin
    #OBJECTS_DIR = ../release/objects
}

HEADERS += \
    BenchmarkTestCase.h \
    ParserTestCase.h \
    XmlSyntaxPrinterTestCase.h

SOURCES += \
    main.cpp \
    BenchmarkTestCase.cpp \
    ParserTestCase.cpp \
    XmlSyntaxPrinterTestCase.cpp

#include
INCLUDEPATH = "../GenericExpressInstanceParser"

#link
unix:LIBS += \
    -L "$$DESTDIR" -lGenericExpressInstanceParser \
    -lfl

#add the bin path to find the GenericExpressInstanceParser lib
release:QMAKE_RPATHDIR += $$DESTDIR

DEFINES += SRCDIR=\\\"$$PWD/\\\"
