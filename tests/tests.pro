QT += core gui printsupport
QT += testlib
QT -= gui

CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle

TARGET = paycheck_tests
TEMPLATE = app

INCLUDEPATH += ../src
DEPENDPATH += $${INCLUDEPATH} # force rebuild if the headers change

BUILDDIR = $$PWD/../build
DESTDIR = $$PWD/../build

OBJECTS_DIR = $$BUILDDIR
MOC_DIR = $$BUILDDIR
RCC_DIR = $$BUILDDIR
UI_DIR = $$BUILDDIR

SOURCES += \
    test_shift.cpp \
    test_schedule.cpp \
    testmain.cpp \
    ../src/dialog_add_shift.cpp \
    ../src/dialog_calculate.cpp \
    ../src/dialog_print.cpp \
    ../src/mainwindow.cpp \
    ../src/registry.cpp \
    ../src/schedule.cpp \
    ../src/shift.cpp

HEADERS += \
    test_shift.h \
    test_schedule.h \
    ../src/dialog_add_shift.h \
    ../src/dialog_calculate.h \
    ../src/dialog_print.h \
    ../src/mainwindow.h \
    ../src/registry.h \
    ../src/schedule.h \
    ../src/shift.h
