//============================================================================
// Name        : mainwindow.h
//============================================================================
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFile>
#include <QTextStream>
#include "./headers/led.h"
#include "./headers/element.h"
#include "./headers/thread_inc.h"
#include "./headers/hall_sensor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

void on_pushButton_led_clicked();

void on_pushButton_kit_clicked();

void on_pushButton_buzzer_clicked();

private:
    Ui::MainWindow *ui;
    Thread_Inc thread_inc;
};

#endif // MAINWINDOW_H