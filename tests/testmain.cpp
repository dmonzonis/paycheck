#include <QtTest/QtTest>

#include "testday.h"
#include "testschedule.h"

int main()
{
    TestDay testDay;
    QTest::qExec(&testDay);

    TestSchedule testSchedule;
    QTest::qExec(&testSchedule);

    return 0;
}
