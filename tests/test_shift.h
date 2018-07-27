#ifndef TESTDAY_H
#define TESTDAY_H

#include <QtTest/QtTest>
#include <QTime>

#include "shift.h"

class TestShift : public QObject
{
    Q_OBJECT
private slots:
    void init();
    void cleanup();
    // Test cases
    void testGetWorkingHours();
    void testToString();

private:
    QTime *time1, *time2;
    Shift *shift;
};

#endif // TESTDAY_H
