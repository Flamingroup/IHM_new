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
    parseurs/retour/parseurretour0r1.cpp \
    parseurs/retour/parseurretour0r2.cpp \
    parseurs/envoi/parseurenvoi.cpp \
    capteurs/capteur.cpp \
    stationmeteo.cpp \
    ordermeteostation/ordermeteostation.cpp \
    ordermeteostation/order0r1.cpp \
    ordermeteostation/order0r2.cpp \
    ordermeteostation/order0r3.cpp \
    ordermeteostation/order0r5.cpp \
    parseurs/retour/parseurretour0r5.cpp \
    plot.cpp \
    parseurs/retour/parseurretour0r3.cpp

HEADERS  += mainwindow.h \
    communication/communication.h \
    communication/serialport.h \
    communication/portselection.h \
    parseurs/retour/parseurretour.h \
    parseurs/retour/parseurretour0r2.h \
    parseurs/retour/parseurretour0r1.h \
    parseurs/envoi/parseurenvoi.h \
    capteurs/capteur.h \
    stationmeteo.h \
    ordermeteostation/ordermeteostation.h \
    ordermeteostation/order0r1.h \
    ordermeteostation/order0r2.h \
    ordermeteostation/order0r3.h \
    ordermeteostation/order0r5.h \
    parseurs/retour/parseurretour0r3.h \
    parseurs/retour/parseurretour0r5.h \
    plot.h

FORMS    += mainwindow.ui
