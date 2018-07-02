#ifndef DIALOG_ADD_SHIFT_H
#define DIALOG_ADD_SHIFT_H

#include <QDialog>
#include <QTime>
#include <QWidget>

namespace Ui {
class DialogAddShift;
}

class DialogAddShift : public QDialog
{
    Q_OBJECT
public:
    explicit DialogAddShift(QWidget *parent = nullptr);
    ~DialogAddShift();
    bool hasAccepted() const;
    QTime getEntryTime() const;
    QTime getExitTime() const;

private slots:
    void on_btnAccept_clicked();
    void on_btnCancel_clicked();

private:
    Ui::DialogAddShift *ui;
    QTime entryTime, exitTime;
    bool accepted;
};

#endif // DIALOG_ADD_SHIFT_H
