QT += core
QT -= gui

TARGET = test
CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle

QMAKE_CXXFLAGS += -std=c++0x
QMAKE_LFLAGS+= -std=c++11

TEMPLATE = app

SOURCES += main.cpp \
    network.cpp \
    protocol.cpp \
    business_logic.cpp \
    casablanca.cpp \
    cas2.cpp \
    client.cpp \
    server.cpp

HEADERS += \
    network.h \
    protocol.h \
    business_logic.h

