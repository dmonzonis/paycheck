#ifndef TESTSCHEDULE_H
#define TESTSCHEDULE_H

#include <QtTest/QtTest>

#include "schedule.h"

class TestSchedule : public QObject
{
    Q_OBJECT
private slots:
    void init();
    void cleanup();
    // Test cases
    void testGetWorkingHours();
    void testGetShiftStrings();
    void testRemoveShift();
    void testRemoveShiftEmpty();

private:
    Schedule *schedule;
};

#endif // TESTSCHEDULE_H
