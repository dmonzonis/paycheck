include(../defaults.pri)

QT += core gui
QT += widgets

TEMPLATE = lib

TARGET = paycheck
SUBDIRS += ui

src.commands += $${QMAKE_MKDIR} $$BUILDDIR

FORMS += ui/*.ui

SOURCES += \
    shift.cpp \
    schedule.cpp \
    mainwindow.cpp \
    dialog_add_shift.cpp \
    dialog_calculate.cpp \
    registry.cpp

HEADERS += \
    shift.h \
    schedule.h \
    mainwindow.h \
    dialog_add_shift.h \
    dialog_calculate.h \
    registry.h

RESOURCES += \
    ../resources.qrc
