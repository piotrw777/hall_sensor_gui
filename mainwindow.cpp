#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "wiringPi.h"
#include "element.h"
#include "led.h"
#include "wheel.h"
#include "hall_sensor.h"
#include <pthread.h>

#define led_pin 21
#define led_pin2 16
#define hall_pin 18

int element::liczba_elementow = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    QObject::connect(&magnet_counter, SIGNAL(valueChanged(int)), ui->lcd_magnet, SLOT(display(int)));

    a3144 = new hall_sensor(hall_pin);

    led reddy1(led_pin);
    led reddy2(led_pin2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    static wheel bike(33);
    a3144->measure_speed(bike, magnet_counter);
}
