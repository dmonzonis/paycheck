#ifndef DIALOG_PRINT_H
#define DIALOG_PRINT_H

#include <QDialog>

#include "schedule.h"

namespace Ui {
class DialogPrint;
}

class DialogPrint : public QDialog
{
    Q_OBJECT
public:
    explicit DialogPrint(QWidget *parent = 0, const Schedule &schedule = Schedule());
    ~DialogPrint();

private slots:
    void on_btnPrint_clicked();

private:
    Ui::DialogPrint *ui;
    const Schedule schedule;
};

#endif // DIALOG_PRINT_H
