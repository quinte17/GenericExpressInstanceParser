#-------------------------------------------------
#
# Project created by QtCreator 2014-11-12T19:21:37
#
#-------------------------------------------------

QT       -= gui

TARGET = GenericExpressInstanceParser
TEMPLATE = lib
CONFIG(debug, debug|release) {
    DESTDIR = ../debug/bin
    OBJECTS_DIR = ../debug/objects
}

CONFIG(release, debug|release) {
    DESTDIR = ../release/bin
    OBJECTS_DIR = ../release/objects
}


#bison config
BISON_PARSER_NAME = ExpressInstanceParser.y
bison.name = bison
bison.commands = bison -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_IN}
bison.input = BISON_PARSER_NAME
bison.output = ExpressInstanceParser.cpp
bison.variable_out = SOURCES
bison.depends = ExpressInstanceParser.y
bison.CONFIG += target_predeps
QMAKE_EXTRA_COMPILERS += bison

#flex config
FLEX_SCANNER_NAME = ExpressInstanceScanner.l
flex.name = flex
flex.commands = flex --outfile=${QMAKE_FILE_OUT} -+ ${QMAKE_FILE_IN}
flex.input = FLEX_SCANNER_NAME
flex.output = ExpressInstanceScanner.cpp
flex.variable_out = SOURCES
flex.depends = ExpressInstanceScanner.l ExpressInstanceScanner.h
flex.CONFIG += target_predeps
QMAKE_EXTRA_COMPILERS += flex

DEFINES += GENERIC_EXPRESS_INSTANCE_PARSER_LIBRARY

#Parser files
HEADERS += \
    GenericExpressInstanceParser.h\
    GenericExpressInstanceParser_Global.h \
    ExpressInstanceScanner.h \
    ExpressTypes.h

SOURCES += \
    GenericExpressInstanceParser.cpp \
    ExpressTypes.cpp

#Visitors
HEADERS += \
    ExpressInstanceVisitor.h \
    ExpressSyntaxPrinter.h \
    XmlSyntaxPrinter.h

SOURCES += \
    ExpressInstanceVisitor.cpp \
    ExpressSyntaxPrinter.cpp \
    XmlSyntaxPrinter.cpp

OTHER_FILES += \
    ExpressInstanceScanner.l \
    ExpressInstanceParser.y \
    External_links.h

#QMAKE_CXXFLAGS += -std=c++11
