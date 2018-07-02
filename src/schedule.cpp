#include "schedule.h"

#include <fstream>

#include "registry.h"

Schedule::Schedule()
{
}

float Schedule::getWorkingHours(const QDate &fromDate, const QDate &toDate) const
{
    float total = 0.f;
    QDate current = fromDate;
    while (current <= toDate)
    {
        // Add the working hours of the current day
        total += getWorkingHours(current);
        // Advance one day
        current = current.addDays(1);
    }
    return total;
}

float Schedule::getWorkingHours(const QDate &date) const
{
    float total = 0.f;
    auto shifts = workingDays.value(date);
    // Add the total of hours on all shifts in that day
    for (Shift shift : shifts)
    {
        total += shift.getWorkingHours();
    }
    return total;
}

void Schedule::addShift(const QDate &date, const QTime &entryTime, const QTime &exitTime)
{
    // Get shifts on that day, if any
    auto shifts = workingDays.value(date);
    // Add new shift
    shifts.push_back(Shift(entryTime, exitTime));
    // Update the shifts for that day in the hash, or create a new entry
    workingDays.insert(date, shifts);
}

std::vector<std::string> Schedule::getShiftStrings(const QDate &date) const
{
    std::vector<std::string> result;
    auto shifts = workingDays.value(date);
    for (Shift shift : shifts)
    {
        result.push_back(shift.toString());
    }
    return result;
}

void Schedule::removeShift(const QDate &date, int index)
{
    auto shifts = workingDays.value(date);
    // Check that there's something to delete
    if (shifts.size() > index && index != -1)
    {
        // Remove the shift at position index
        shifts.erase(shifts.begin() + index);
        // Update the shift in the hash
        workingDays.insert(date, shifts);
    }
}

Schedule Schedule::loadSchedule()
{
    // Create new empty schedule
    Schedule schedule;

    // Open data file
    // TODO: Search for file in the executable absolute path
    std::ifstream dataFile(DATA_FILENAME);
    if (!dataFile)
    {
        // TODO: Make registry error class
        throw std::runtime_error("Error opening data file.");
    }
    std::string input, delimiter=",";
    while (std::getline(dataFile, input))
    {
        // Parse data in the line
        // Schedule data is stored as date,entryTime,exitTime
        auto parts = split(input, delimiter);
        QDate date = QDate::fromString(parts.at(0), DATE_FORMAT);
        QTime entryTime = QTime::fromString(parts.at(1), TIME_FORMAT);
        QTime exitTime = QTime::fromString(parts.at(2), TIME_FORMAT);
        // Add shift to the schedule
        schedule.addShift(date, entryTime, exitTime);
    }
}

void Schedule::saveSchedule()
{
    // TODO: Implement
}
