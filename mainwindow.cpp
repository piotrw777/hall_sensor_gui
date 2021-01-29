//============================================================================
// Name        : mainwindow.cpp
//============================================================================
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
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

