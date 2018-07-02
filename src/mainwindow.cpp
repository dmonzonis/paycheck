#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>

#include "dialog_add_shift.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
