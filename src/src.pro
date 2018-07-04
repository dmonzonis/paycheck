include(../defaults.pri)

QT += core gui
QT += widgets printsupport

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
