#-------------------------------------------------
#
# Project created by QtCreator 2017-02-13T10:32:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = highway
TEMPLATE = app


SOURCES += main.cpp\
        highwaywindow.cpp \
    lane.cpp

HEADERS  += highwaywindow.h \
    lane.h

FORMS    += highwaywindow.ui

DISTFILES +=

RESOURCES += \
    resources.qrc
