#-------------------------------------------------
#
# Project created by QtCreator 2018-01-02T17:00:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTpcvGraph
TEMPLATE = app


SOURCES += main.cpp\
        LeonWgt.cpp \
    LTpcvView.cpp \
    LCoordinateItem.cpp

HEADERS  += LeonWgt.h \
    LTpcvView.h \
    LCoordinateItem.h \
    LCommon.h

FORMS    += LeonWgt.ui
