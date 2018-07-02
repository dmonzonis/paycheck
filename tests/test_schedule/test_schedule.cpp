#include "test_schedule.h"

void TestSchedule::init()
{
    schedule = new Schedule();
}

void TestSchedule::cleanup()
{
    delete schedule;
}

void TestSchedule::testGetWorkingHours()
{
    QVERIFY(schedule->getWorkingHours(QDate(2017, 1, 1), QDate(2019, 1, 1)) == 0.f);
    schedule->addShift(QDate(2018, 6, 15), QTime(8, 0), QTime(15, 0));
    QVERIFY(schedule->getWorkingHours(QDate(2017, 1, 1), QDate(2019, 1, 1)) == 7.f);
    schedule->addShift(QDate(2017, 1, 6), QTime(17, 0), QTime(20, 30));
    QVERIFY(schedule->getWorkingHours(QDate(2017, 1, 1), QDate(2019, 1, 1)) == 10.5f);
    QVERIFY(schedule->getWorkingHours(QDate(2017, 1, 1), QDate(2018, 2, 2)) == 3.5f);
    QVERIFY(schedule->getWorkingHours(QDate(2018, 3, 3), QDate(2018, 7, 2)) == 7.f);
    QVERIFY(schedule->getWorkingHours(QDate(2019, 1, 1), QDate(2019, 6, 9)) == 0.f);
}

void TestSchedule::testGetShiftStrings()
{
    // Day with shifts
    QDate date(2018, 6, 15);
    schedule->addShift(date, QTime(8, 0), QTime(15, 0));
    schedule->addShift(date, QTime(17, 0), QTime(20, 30));
    auto shiftStrings = schedule->getShiftStrings(date);
    QVERIFY(shiftStrings.size() == 2);
    QCOMPARE(shiftStrings[0], "8:00 - 15:00");
    QCOMPARE(shiftStrings[1], "17:00 - 20:30");

    // Day with no shifts
    shiftStrings = schedule->getShiftStrings(QDate(2017, 5, 5));
    QVERIFY(shiftStrings.empty());
}

void TestSchedule::testRemoveShift()
{
    // Remove shift from day with multiple shifts
    QDate date(2018, 6, 15);
    schedule->addShift(date, QTime(8, 0), QTime(15, 0));
    schedule->addShift(date, QTime(17, 0), QTime(20, 30));
    auto shiftStrings = schedule->getShiftStrings(date);
    auto secondShift = shiftStrings[1];
    QVERIFY(shiftStrings.size() == 2);
    schedule->removeShift(date, 0);
    shiftStrings = schedule->getShiftStrings(date);
    QVERIFY(shiftStrings.size() == 1);
    QCOMPARE(shiftStrings[0], secondShift);

    // Remove shift from day with single shift
    schedule->removeShift(date, 0);
    shiftStrings = schedule->getShiftStrings(date);
    QVERIFY(shiftStrings.empty());
}

void TestSchedule::testRemoveShiftEmpty()
{
    // Remove non-existant shift
    QDate date(2018, 6, 15);
    auto shiftStrings = schedule->getShiftStrings(date);
    QVERIFY(shiftStrings.empty());
    schedule->removeShift(date, 5);
    schedule->removeShift(date, -2);
    schedule->removeShift(date, 0);
    shiftStrings = schedule->getShiftStrings(date);
    QVERIFY(shiftStrings.empty());
}



QTEST_APPLESS_MAIN(TestSchedule)
