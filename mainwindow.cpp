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
    thread_inc(), yellow(12)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    yellow.on();
}

void MainWindow::on_pushButton_led_clicked()
{
    if(ui->pushButton_led->text() == "Led On")
    {
        ui->pushButton_led->setText("Led Off");
    }
    else
    {
        ui->pushButton_led->setText("Led On");
    }
    thread_inc.startOrstopThreadA();
}

void MainWindow::on_pushButton_kit_clicked()
{
    if(ui->pushButton_kit->text() == "Kit On")
    {
        ui->pushButton_kit->setText("Kit Off");
    }
    else
    {
        ui->pushButton_kit->setText("Kit On");
    }
    thread_inc.startOrstopThreadB();

}
