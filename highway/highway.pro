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
    car.cpp \
    laneview.cpp \
    settings.cpp \
    manipulator.cpp \
    highway.cpp

HEADERS  += \
    lane.h \
    car.h \
    laneview.h \
    settings.h \
    manipulator.h \
    highway.h

FORMS    += \
    manipulator.ui

DISTFILES +=

RESOURCES += \
    resources.qrc
