QT += core gui
QT += widgets printsupport

CONFIG += c++11

TARGET = paycheck
TEMPLATE = app

FORMS += ui/*.ui

BUILDDIR = $$PWD/../build
DESTDIR = $$PWD/../bin

OBJECTS_DIR = $$BUILDDIR
MOC_DIR = $$BUILDDIR
RCC_DIR = $$BUILDDIR
UI_DIR = $$BUILDDIR

SOURCES += \
    main.cpp \
    shift.cpp \
    schedule.cpp \
    mainwindow.cpp \
    dialog_add_shift.cpp \
    dialog_calculate.cpp \
    registry.cpp \
    dialog_print.cpp

HEADERS += \
    shift.h \
    schedule.h \
    mainwindow.h \
    dialog_add_shift.h \
    dialog_calculate.h \
    registry.h \
    dialog_print.h

RESOURCES += \
    ../resources.qrc
