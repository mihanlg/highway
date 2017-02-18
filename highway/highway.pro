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
    lane.cpp \
    highway.cpp \
    car.cpp \
    laneview.cpp \
    settings.cpp

HEADERS  += \
    lane.h \
    highway.h \
    car.h \
    laneview.h \
    settings.h

FORMS    += \
    highway.ui

DISTFILES +=

RESOURCES += \
    resources.qrc
