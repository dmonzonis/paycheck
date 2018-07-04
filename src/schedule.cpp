#include "schedule.h"

#include <fstream>
#include <QFileDialog>
#include <QPrinter>
#include <QString>
#include <QTextDocument>

#include "registry.h"

float Schedule::getWorkingHours(const QDate &dateFrom, const QDate &dateTo) const
{
    float total = 0.f;
    // Iterate between all dates one by one, adding the working hours if it has any shifts
    QDate current = dateFrom;
    while (current <= dateTo)
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
    // TODO: Use QFile instead of fstream
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
    return schedule;
}

void Schedule::saveSchedule()
{
    // TODO: Use QFile instead of fstream
    std::ofstream dataFile(DATA_FILENAME);
    // Iterate through all shifts, and save them to file
    for (auto it = workingDays.begin(); it != workingDays.end(); ++it)
    {
        std::string date = it.key().toString(DATE_FORMAT).toStdString();
        for (Shift shift : it.value())
        {
            std::string entryTime = shift.getEntryTime().toString(TIME_FORMAT).toStdString();
            std::string exitTime = shift.getExitTime().toString(TIME_FORMAT).toStdString();
            // Write the shift to the file
            dataFile << date << "," << entryTime << "," << exitTime << "\n";
        }
    }
}

void Schedule::printSchedule(const QDate &dateFrom, const QDate &dateTo) const
{
    // Ask user for filename
    QString filename = QFileDialog::getSaveFileName(
                nullptr,
                "Exportar a PDF",
                QString(),
                "*.pdf"
                );

    // Append pdf extension if user didn't provide it
    if (QFileInfo(filename).suffix().isEmpty())
    {
        filename.append(".pdf");
    }

    // Initialize printer
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(filename);

    // Get HTML and format text document
    QString html = toHtml(dateFrom, dateTo);
    QTextDocument doc;
    doc.setHtml(html);
    doc.setPageSize(printer.pageRect().size());

    // Print the document to pdf
    doc.print(&printer);
}

QString Schedule::toHtml(const QDate &dateFrom, const QDate &dateTo) const
{
    QString html;
    // Iterate between the dates, adding formatted HTML representing the shifts
    QDate current = dateFrom;
    while (current <= dateTo)
    {
        // Only add working days to the HTML
        if (workingDays.contains(current))
        {
            // Add date in bold text to the left of the page
            // TODO: Change format
            html += "<b>" + current.toString() + "</b>";
            // Iterate through all shifts and print them
            for (auto shift : workingDays.value(current))
            {
                // Put it into a center-aligned paragraph
                html += "<p align=\"center\">";
                html += QString::fromStdString(shift.toString()) + "<br>";
                html += "</p>";
            }
            // Add a horizontal bar at the end of the day
            html += "<hr>";
        }

        // Advance one day
        current = current.addDays(1);
    }
    return html;
}
