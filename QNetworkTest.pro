#-------------------------------------------------
#
# Project created by QtCreator 2015-03-29T16:18:03
#
#-------------------------------------------------

QT       += core
QT       += serialport

QT       -= gui

TARGET = QNetworkTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ConsoleSerialPort.cpp \
    DataEmmitter.cpp \
    NTConfig.cpp \
    RealSerialPorts.cpp \
    Utils.cpp

HEADERS += \
    Atoms.h \
    ConsoleSerialPort.h \
    DataEmmitter.h \
    NTConfig.h \
    RealSerialPorts.h \
    Utils.h
