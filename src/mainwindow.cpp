#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopServices>
#include <QTime>
#include <QUrl>
#include <QDebug>

#include "dialog_add_shift.h"
#include "dialog_calculate.h"
#include "dialog_print.h"
#include "registry.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Load registry, or create a default one if it doesn't exist
    try
    {
        registry.loadData();
    }
    catch (const std::exception &ex)
    {
        qDebug() << ex.what() << "Generating default config file.";
        registry.generateDefaultConfigFile();
        registry.loadData();
    }

    // Load schedule data, if it exists
    try
    {
        schedule = Schedule::loadSchedule();
    }
    catch (const std::exception &ex)
    {
        qDebug() << ex.what();
    }

    updateSelectedDay();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addShift(const QTime &entryTime, const QTime &exitTime)
{
    schedule.addShift(selectedDate, entryTime, exitTime);
}

void MainWindow::on_calendar_selectionChanged()
{
    updateSelectedDay();
}

void MainWindow::on_btnAddShift_clicked()
{
    DialogAddShift *dialog = new DialogAddShift(this);
    dialog->exec();
    // Only add shift if the user clicked accept
    if (dialog->hasAccepted())
    {
        addShift(dialog->getEntryTime(), dialog->getExitTime());
        updateSelectedDay();
        // Save new data to file
        schedule.saveSchedule();
    }
    delete dialog;
}

void MainWindow::on_btnRemoveShift_clicked()
{
    // Get selected shift index on the list, starting from 0.
    // Will be -1 if no shift is selected.
    int selectedShiftIndex = ui->listShift->currentRow();
    // Remove the selected shift from the schedule
    schedule.removeShift(selectedDate, selectedShiftIndex);
    // Save new data to file
    schedule.saveSchedule();
    updateSelectedDay();
}

void MainWindow::updateSelectedDay()
{
    // Get currently selected date on the calendar
    selectedDate = ui->calendar->selectedDate();
    // Update shift list with the selected day's shifts
    ui->listShift->clear();
    for (auto shiftString : schedule.getShiftStrings(selectedDate))
    {
        ui->listShift->addItem(QString::fromStdString(shiftString));
    }
}

void MainWindow::on_actionCalculate_triggered()
{
    // Open calculate dialog
    DialogCalculate *dialog = new DialogCalculate(this,
                                                  schedule,
                                                  registry.getHourlyWage(),
                                                  registry.getCurrency());
    dialog->show();
}

void MainWindow::on_actionPrint_triggered()
{
    // Open print dialog
    DialogPrint *dialog = new DialogPrint(this, schedule);
    dialog->show();
}

void MainWindow::on_actionConfig_triggered()
{
    // TODO: Use a custom config dialog to change configuration instead of opening the text file
    QDesktopServices::openUrl(QUrl(QString::fromStdString(CONFIG_FILENAME)));
}
