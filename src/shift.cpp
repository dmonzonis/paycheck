#include "shift.h"

Shift::Shift(QTime entryTime, QTime exitTime)
    : entryTime(entryTime),
      exitTime(exitTime)
{
}

float Shift::getWorkingHours() const
{
    return entryTime.msecsTo(exitTime) / (1000.f * 60 * 60);
}

QTime Shift::getEntryTime() const
{
    return entryTime;
}

QTime Shift::getExitTime() const
{
    return exitTime;
}

std::string Shift::toString() const
{
    std::string result = "";
    result += entryTime.toString("h:mm").toStdString();
    result += " - ";
    result += exitTime.toString("h:mm").toStdString();
    return result;
}
