#include <QtTest/QtTest>

#include "test_schedule.h"
#include "test_shift.h"

int main()
{

    TestShift testShift;
    QTest::qExec(&testShift);

    TestSchedule testSchedule;
    QTest::qExec(&testSchedule);

    return 0;
}
