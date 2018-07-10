#include "dialog_print.h"
#include "ui_dialog_print.h"

DialogPrint::DialogPrint(QWidget *parent, const Schedule &schedule)
    : QDialog(parent),
      ui(new Ui::DialogPrint),
      schedule(schedule)
{
    ui->setupUi(this);
    // Set dates to current date
    ui->dateFrom->setDate(QDate::currentDate());
    ui->dateTo->setDate(QDate::currentDate());
}

DialogPrint::~DialogPrint()
{
    delete ui;
}

void DialogPrint::on_btnPrint_clicked()
{
    bool printHours = ui->cbTotalHours->isChecked();
    bool compactMode = ui->cbCompactMode->isChecked();
    schedule.printSchedule(ui->dateFrom->date(), ui->dateTo->date(),
                           printHours, compactMode);
    this->close();
}
