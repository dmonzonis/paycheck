#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <vector>

#include <QHash>
#include <QDate>

#include "shift.h"

/**
 * @brief The Schedule class is used to store and use information about all the work shifts
 * for each date.
 */
class Schedule
{
public:
    Schedule() = default;

    /**
     * @brief Return the total working hours between two dates, both inclusive.
     *
     * It will take into account all the shifts in the dates that are within the range, and
     * add them up for a total of working hours.
     */
    float getWorkingHours(const QDate &dateFrom, const QDate &dateTo) const;

    /**
     * @brief Return the total working hours on a single date.
     *
     * It will take into account all the shifts of the given date, and add them up for a total
     * of working hours.
     */
    float getWorkingHours(const QDate &date) const;

    /**
     * @brief Add a shift with given entry and exit times for a given date.
     *
     * If the date already contains a shift, it will be appended to the shifts of that date.
     */
    void addShift(const QDate &date, const QTime &entryTime, const QTime &exitTime);

    /**
     * @brief Return a vector with the strings representing each shift for a given date.
     * @see Shift
     */
    std::vector<std::string> getShiftStrings(const QDate &date) const;

    /**
     * @brief Remove a shift from the given date, determined by the index in the list of shifts
     * of that shift.
     *
     * If the given date doesn't have any shift in that index, it will do nothing.
     */
    void removeShift(const QDate &date, int index);

    /**
     * @brief Load and return a schedule from a saved schedule file.
     *
     * It will throw an error if a data file could not be found or opened correctly.
     * The filename of the data file is given by the constants defined in the registry header.
     *
     * @see Registry
     */
    static Schedule loadSchedule();

    /**
     * @brief Save the schedule to a data file, overriding the previous one.
     *
     * The filename of the data file is given by the constants defined in the registry header.
     */
    void saveSchedule();

    /**
     * @brief Print the schedule between two given dates to PDF format.
     * @param dateFrom Starting date for the printed schedule. It will be included.
     * @param dateTo End date for the printed schedule. It will be included.
     */
    void printSchedule(const QDate &dateFrom, const QDate &dateTo) const;

private:
    /**
     * @brief Return the schedule between two dates in HTML format, ready for printing.
     */
    QString toHtml(const QDate &dateFrom, const QDate &dateTo) const;

private:
    QHash<QDate, std::vector<Shift>> workingDays;
};

#endif // SCHEDULE_H
