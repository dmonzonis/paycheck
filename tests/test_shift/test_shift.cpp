#include "test_shift.h"

#include <vector>

void TestShift::init()
{
    time1 = new QTime(8, 0);
    time2 = new QTime(15, 0);
    shift = new Shift(*time1, *time2);
}

void TestShift::cleanup()
{
    delete shift;
    delete time1;
    delete time2;
}

void TestShift::testGetWorkingHours()
{
    QVERIFY(shift->getWorkingHours() == 7.f);
    QTime time3(17, 0);
    QTime time4(20, 30);
    Shift shift2(time3, time4);
    QVERIFY(shift2.getWorkingHours() == 3.5f);
}

void TestShift::testToString()
{
    std::string shiftString = shift->toString();
    QVERIFY(!shiftString.empty());
    QCOMPARE(shiftString, "8:00 - 15:00");
}

QTEST_APPLESS_MAIN(TestShift)
