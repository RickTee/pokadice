# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/GNU-Linux
TARGET = QtPokaDice
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += link_pkgconfig debug 
PKGCONFIG += glib-2.0
QT = core gui widgets
SOURCES += main.cpp rkDialog.cpp rkDice.cpp rkDiceControl.cpp rkPokadice.cpp rkPrefs.cpp rkScorecard.cpp
HEADERS += rkDialog.h rkDice.h rkDiceControl.h rkPokadice.h rkPrefs.h rkScorecard.h version.h
FORMS +=
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += 
equals(QT_MAJOR_VERSION, 4) {
QMAKE_CXXFLAGS += -std=c++14
}
