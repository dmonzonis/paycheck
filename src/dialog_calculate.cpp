#include "dialog_calculate.h"
#include "ui_dialog_calculate.h"

#include <QDate>

DialogCalculate::DialogCalculate(QWidget *parent, const Schedule &schedule) :
    QDialog(parent),
    ui(new Ui::DialogCalculate),
    schedule(schedule)
{
    ui->setupUi(this);
    // Set dates to current date
    ui->dateFrom->setDate(QDate::currentDate());
    ui->dateTo->setDate(QDate::currentDate());
}

DialogCalculate::~DialogCalculate()
{
    delete ui;
}

void DialogCalculate::on_btnAccept_clicked()
{
    this->close();
}

void DialogCalculate::on_dateFrom_dateChanged()
{
    updateResults();
}

void DialogCalculate::on_dateTo_dateChanged()
{
    updateResults();
}

void DialogCalculate::updateResults()
{
    // Get total working hours between the two dates, both inclusive
    QDate dateFrom = ui->dateFrom->date();
    QDate dateTo = ui->dateTo->date();
    float hours = schedule.getWorkingHours(dateFrom, dateTo);
    // Update with results
    ui->resultHours->setText(QString::number(hours) + " h");
}
