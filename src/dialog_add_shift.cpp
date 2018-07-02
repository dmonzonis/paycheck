#include "dialog_add_shift.h"
#include "ui_dialog_add_shift.h"

DialogAddShift::DialogAddShift(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::DialogAddShift),
      accepted(false)
{
    ui->setupUi(this);
}

DialogAddShift::~DialogAddShift()
{
    delete ui;
}

bool DialogAddShift::hasAccepted() const
{
    return accepted;
}

QTime DialogAddShift::getEntryTime() const
{
    return entryTime;
}

QTime DialogAddShift::getExitTime() const
{
    return exitTime;
}

void DialogAddShift::on_btnAccept_clicked()
{
    entryTime = ui->timeFrom->time();
    exitTime = ui->timeTo->time();
    accepted = true;
    this->close();
}

void DialogAddShift::on_btnCancel_clicked()
{
    this->close();
}
