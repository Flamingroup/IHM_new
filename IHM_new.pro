#-------------------------------------------------
#
# Project created by QtCreator 2014-02-23T12:48:02
#
#-------------------------------------------------

QT       += core gui
TARGET = IHM_new
TEMPLATE = app

QMAKE_CXXFLAGS +=   -std=c++11

CONFIG += qwt
CONFIG += extserialport

include(/usr/local/qwt-6.1.0/features/qwt.prf)
include(3rdparty/qextserialport/src/qextserialport.pri)
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets




SOURCES += main.cpp\
        mainwindow.cpp \
    communication/communication.cpp \
    communication/serialport.cpp \
    communication/portselection.cpp \
    parseurs/retour/parseurretour.cpp \
    capteurs/capteur.cpp \
    stationmeteo.cpp \
    plot.cpp \
    convertisseur.cpp

HEADERS  += mainwindow.h \
    communication/communication.h \
    communication/serialport.h \
    communication/portselection.h \
    parseurs/retour/parseurretour.h \
    capteurs/capteur.h \
    stationmeteo.h \
    plot.h \
    convertisseur.hpp

FORMS    += mainwindow.ui
