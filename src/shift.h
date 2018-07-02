#ifndef SHIFT_H
#define SHIFT_H

#include <QTime>

/**
 * @brief The Shift class represents a range of working hours, from entry time
 * to exit time.
 *
 * Entry and exit times are represented by QTime objects.
 */
class Shift
{
public:
    /**
     * @brief Create a new shift with the given entry and exit times.
     */
    Shift(QTime entryTime, QTime exitTime);

    /**
     * @brief Return the total of hours in the range from entry to exit time.
     */
    float getWorkingHours() const;

    /**
     * @brief Return the entry time.
     */
    QTime getEntryTime() const;

    /**
     * @brief Return the exit time.
     */
    QTime getExitTime() const;

    /**
     * @brief Return a string representing the shift.
     *
     * The format of the string is "h:mm - h:mm", starting with the entry time and
     * ending with the exit time.
     *
     * For example, if entry time is 8:00 and exit time is 13:30, the returned string
     * will be "8:00 - 13:30".
     */
    std::string toString() const;

private:
    QTime entryTime, exitTime;
};

#endif // SHIFT_H
