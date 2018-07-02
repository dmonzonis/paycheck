#ifndef DIALOG_CALCULATE_H
#define DIALOG_CALCULATE_H

#include <QDialog>
#include <QString>

#include "schedule.h"

namespace Ui {
class DialogCalculate;
}

class DialogCalculate : public QDialog
{
    Q_OBJECT
public:
    explicit DialogCalculate(QWidget *parent = 0, const Schedule &schedule = Schedule(),
                             float hourlyWage = 0.f, QString currency = "$");
    ~DialogCalculate();

private slots:
    void on_btnAccept_clicked();
    void on_dateFrom_dateChanged();
    void on_dateTo_dateChanged();

private:
    void updateResults();

private:
    Ui::DialogCalculate *ui;
    const Schedule schedule;
    float hourlyWage;
    QString currency;
};

#endif // DIALOG_CALCULATE_H
