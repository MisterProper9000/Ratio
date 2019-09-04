#-------------------------------------------------
#
# Project created by QtCreator 2019-06-29T17:50:44
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = IRatio
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    IRatioImpl.cpp

HEADERS += \
    IRatio.h \
    error.h \
    ILog.h \
    SHARED_EXPORT.h

LIBS += "..\IRatio-build-desktop-Qt_4_7_4__mingw_________\debug\ILog.dll"
QMAKE_CXXFLAGS += -std=gnu++0x




