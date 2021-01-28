//============================================================================
// Name        : mainwindow.h
//============================================================================
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFile>
#include <QTextStream>
#include "value.h"
#include "element.h"

class hall_sensor;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
friend class hall_sensor;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    value speed_value;
    value rpm_value;
    value distance_value;
    value magnet_counter;
    hall_sensor *a3144;

};

#endif // MAINWINDOW_H
