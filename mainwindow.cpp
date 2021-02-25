//=============================================================
// Name        : mainwindow.cpp
//=============================================================
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "element.h"
#include "led.h"
#include "hall_sensor.h"
#include "thread_inc.h"
#include "unitchanger.h"
#include "dialog.h"

#include <wiringPi.h>
#include <QCloseEvent>
#include <QDate>
#include <QMessageBox>
#include <QTimer>
#include <QDebug>
#include <pthread.h>

#define update_date 1
//#include "circle.h"

/*
#define led_pin 21
#define led_pin2 16
#define hall_pin 18
*/
int element::liczba_elementow = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    thread_inc()
    //unitchgr()
{
    ui->setupUi(this);

    ui->comboBox->addItem("km/h");
    ui->comboBox->addItem("m/s");
    ui->comboBox->addItem("mph");

    //updating date
#if(update_date == 1)
    QTimer *timer = new QTimer(this);

    QObject::connect(timer, &QTimer::timeout, this, &MainWindow::showDate);
    timer->start(1000);
    showDate();
#endif
    //change speed
    QObject::connect(thread_inc.threadC.elem,
                    SIGNAL(speed_change(double)), ui->speedmeter, SLOT(changeValue(double)));
    //rpm change
    QObject::connect(thread_inc.threadC.elem,
                    SIGNAL(rpm_change(int)), ui->lcd_rpm, SLOT(display(int)));
    //distance change
    QObject::connect(thread_inc.threadC.elem,
                    SIGNAL(distance_change(QString)), ui->lcd_distance, SLOT(display(QString)));
    //time trip change
    QObject::connect(thread_inc.threadC.elem,
                    SIGNAL(time_trip_change(QString)), ui->lcd_time_trip, SLOT(display(QString)));
    //average_speed_change
    QObject::connect(thread_inc.threadC.elem,
                    SIGNAL(average_speed_change(QString)), ui->lcd_avg_speed, SLOT(display(QString)));
    //speed limit buzzer
    QObject::connect(thread_inc.threadC.elem,
                    SIGNAL(speed_limit_exceed()), &thread_inc, SLOT(startThreadB()));
    QObject::connect(thread_inc.threadC.elem,
                    SIGNAL(speed_normal()), &thread_inc, SLOT(stopThreadB()));
    //speed limit -> blue led
    QObject::connect(thread_inc.threadC.elem,
                    SIGNAL(speed_limit_exceed()), &thread_inc, SLOT(startThreadD()));
    QObject::connect(thread_inc.threadC.elem,
                    SIGNAL(speed_normal()), &thread_inc, SLOT(stopThreadD()));
    //kit effect
    QObject::connect(thread_inc.threadC.elem,
                    SIGNAL(start_moving()), &thread_inc, SLOT(startThreadE()));
    QObject::connect(thread_inc.threadC.elem,
                    SIGNAL(stop_moving()), &thread_inc, SLOT(stopThreadE()));

    //change radius
    QObject::connect(ui->spinBox_radius, SIGNAL(valueChanged(int)),
                     thread_inc.threadC.elem, SLOT(change_radius(int)));

    //comboBox -> unitchgr
    //QObject::connect(ui->comboBox, SIGNAL(currentIndexChanged(int)),
      //               &unitchgr, SLOT(change_unitNumber(int)));

    //comboBox -> hall sensor
    QObject::connect(ui->comboBox, SIGNAL(currentIndexChanged(int)),
                    thread_inc.threadC.elem, SLOT(change_unit(int)));

    //comboBox -> speedometer
    QObject::connect(ui->comboBox, SIGNAL(currentIndexChanged(int)),
                    ui->speedmeter, SLOT(change_unitNr(int)));

    thread_inc.startOrstopThreadA(); //yellow lamp
    thread_inc.startOrstopThreadC(); //hall_sensor
    LoadSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
      //event->ignore();
      //if (QMessageBox::Yes == QMessageBox::question(this, "Close Confirmation", "Exit?", QMessageBox::Yes | QMessageBox::No)) {
       // event->accept();
        SaveSettings();
      //}
}

void MainWindow::LoadSettings()
{
    QSettings setting(ORGANIZATION_NAME,APPLICATION_NAME);
    int radius = setting.value("radius").toInt();
    int unit_index = setting.value("units").toInt();
    QRect rect = setting.value("position").toRect();

    this->setGeometry(rect);
    ui->spinBox_radius->setValue(radius);
    qDebug() << "Settingsy zaladowane !!!\n";
    ui->comboBox->setCurrentIndex(unit_index);
}

void MainWindow::SaveSettings()
{
    QSettings setting(ORGANIZATION_NAME,APPLICATION_NAME);
    setting.setValue("units", ui->comboBox->currentIndex());
    setting.setValue("radius", ui->spinBox_radius->value());
    setting.setValue("position", this->geometry());
}

void MainWindow::showDate()
{
    QDate date;
    QTime time;
    QString dateString;
    QString timeString;

    date = QDate::currentDate();
    time = QTime::currentTime();

    dateString = date.toString("dd.MM.yyyy");
    timeString = time.toString("hh:mm:ss");

    if(time.second() % 2 == 1) {
        timeString[2] = ' ';
        timeString[5] = ' ';
    }
    else {

    }
    ui->label_date->setText(QString("  ")+dateString+QString("  ")+timeString);
}
void MainWindow::startDialog()
{
    Dialog *mydialog = new Dialog(this);
    QObject::connect(mydialog, &Dialog::angleChanged, ui->speedmeter, &speedometer::setAngle);
    QObject::connect(mydialog, &Dialog::maxSpeedChanged, ui->speedmeter, &speedometer::setMax_speed);
    QObject::connect(mydialog, &Dialog::stepChanged, ui->speedmeter, &speedometer::setStep);

    mydialog->setModal(false);
    mydialog->show();
    mydialog->activateWindow();
}
void MainWindow::on_pushButton_settings_clicked()
{
    startDialog();

//    QObject::connect(mydialog, &Dialog::redChanged, this, &MainWindow::setArrowColor1);
//    QObject::connect(mydialog, &Dialog::greenChanged, this, &MainWindow::setArrowColor2);
//    QObject::connect(mydialog, &Dialog::blueChanged, this, &MainWindow::setArrowColor3);

//    QObject::connect(mydialog, &Dialog::max_speedChanged, this, &MainWindow::setMax_speed);
//    QObject::connect(mydialog, &Dialog::stepChanged, this, &MainWindow::setStep);

}
