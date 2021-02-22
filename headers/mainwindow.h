//============================================================================
// Name        : mainwindow.h
//============================================================================
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFile>
#include <QTextStream>
#include <QSettings>
#include "led.h"
#include "element.h"
#include "thread_inc.h"
#include "hall_sensor.h"


#define ORGANIZATION_NAME "Peter"
#define ORGANIZATION_DOMAIN "www.com"
#define APPLICATION_NAME "licznik_rowerowy"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent * event);
private slots:

void on_pushButton_led_clicked();

void on_pushButton_kit_clicked();

void on_pushButton_buzzer_clicked();

void LoadSettings();

void SaveSettings();

private:
    Ui::MainWindow *ui;
    Thread_Inc thread_inc;
};

#endif // MAINWINDOW_H
