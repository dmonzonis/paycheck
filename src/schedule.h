#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <vector>

#include <QHash>
#include <QDate>

#include "shift.h"

class Schedule
{
public:
    Schedule();
    float getWorkingHours(const QDate &fromDate, const QDate &toDate) const;
    float getWorkingHours(const QDate &date) const;
    void addShift(const QDate &date, const QTime &entryTime, const QTime &exitTime);
    std::vector<std::string> getShiftStrings(const QDate &date) const;
    void removeShift(const QDate &date, int index);

private:
    QHash<QDate, std::vector<Shift>> workingDays;
};

#endif // SCHEDULE_H
