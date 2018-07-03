include(../defaults.pri)

QT += core gui
QT += widgets

TARGET = paycheck
TEMPLATE = app

SOURCES += \
    main.cpp

LIBS += -L$$DESTDIR -lpaycheck
