#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "schedule.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addShift(const QTime &entryTime, const QTime &exitTime);

private slots:
    void on_calendar_selectionChanged();
    void on_btnAddShift_clicked();
    void on_btnRemoveShift_clicked();

private:
    void updateSelectedDay();

private:
    Ui::MainWindow *ui;
    Schedule schedule;
    QDate selectedDate;
};

#endif // MAINWINDOW_H
