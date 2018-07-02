#ifndef SHIFT_H
#define SHIFT_H

#include <QTime>

class Shift
{
public:
    Shift(QTime entryTime, QTime exitTime);
    float getWorkingHours() const;
    QTime getEntryTime() const;
    QTime getExitTime() const;
    std::string toString() const;

private:
    QTime entryTime, exitTime;
};

#endif // SHIFT_H
