//============================================================================
// Name        : mainwindow.h
//============================================================================
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFile>
#include <QTextStream>
#include "led.h"
#include "element.h"
#include "thread_inc.h"

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

void on_pushButton_led_clicked();

void on_pushButton_kit_clicked();

private:
    Ui::MainWindow *ui;
    Thread_Inc thread_inc;
    led yellow;
};

#endif // MAINWINDOW_H
