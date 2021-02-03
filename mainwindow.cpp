//=============================================================
// Name        : mainwindow.cpp
//=============================================================
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "wiringPi.h"
#include "element.h"
#include "led.h"
#include "wheel.h"
#include "hall_sensor.h"
#include "thread_inc.h"
#include <pthread.h>

#define led_pin 21
#define led_pin2 16
#define hall_pin 18

int element::liczba_elementow = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    thread_inc()
{

    ui->setupUi(this);
    QObject::connect(thread_inc.threadC.elem,
                    SIGNAL(speed_change(double)), ui->lcd_speed, SLOT(display(double)));
    QObject::connect(thread_inc.threadC.elem,
                    SIGNAL(rpm_change(int)), ui->lcd_rpm, SLOT(display(int)));
    QObject::connect(thread_inc.threadC.elem,
                    SIGNAL(distance_change(double)), ui->lcd_distance, SLOT(display(double)));
    QObject::connect(thread_inc.threadC.elem,
                    SIGNAL(time_trip_change(QString)), ui->lcd_time_trip, SLOT(display(QString)));
    QObject::connect(thread_inc.threadC.elem,
                    SIGNAL(average_speed_change(double)), ui->lcd_avg_speed, SLOT(display(double)));
    QObject::connect(thread_inc.threadC.elem,
                    SIGNAL(speed_limit_exceed()), &thread_inc, SLOT(startThreadB()));
    QObject::connect(thread_inc.threadC.elem,
                    SIGNAL(speed_normal()), &thread_inc, SLOT(stopThreadB()));
    //speed limit -> blue led
    QObject::connect(thread_inc.threadC.elem,
                    SIGNAL(speed_limit_exceed()), &thread_inc, SLOT(startThreadD()));
    QObject::connect(thread_inc.threadC.elem,
                    SIGNAL(speed_normal()), &thread_inc, SLOT(stopThreadD()));

    /*
     *                 if(speed * 3.6 > 40 && speed_exceded == false) {
                    speed_exceded = true;
                    emit speed_limit_exceed();
                }
                if(speed * 3.6 <= 40 && speed_exceded == true) {
                    speed_exceded = false;
                    emit speed_normal();
                }
     *
     *
     * */
    thread_inc.startOrstopThreadA(); //yellow lamp
    thread_inc.startOrstopThreadC(); //hall_sensor
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_led_clicked()
{
    if(ui->pushButton_led->text() == "Led Off")
    {
        ui->pushButton_led->setText("Led On");
    }
    else
    {
        ui->pushButton_led->setText("Led Off");
    }
    thread_inc.startOrstopThreadA();
}

void MainWindow::on_pushButton_kit_clicked()
{
    if(ui->pushButton_kit->text() == "Buzzer On")
    {
        ui->pushButton_kit->setText("Buzzer Off");
    }
    else
    {
        ui->pushButton_kit->setText("Buzzer On");
    }
    thread_inc.startOrstopThreadB();

}
