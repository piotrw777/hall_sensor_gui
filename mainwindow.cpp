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
    thread_inc() ,
    edit_state(0)
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
    timer_radius_up = new QTimer(this);
    timer_radius_down = new QTimer(this);

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

    //main button
    QObject::connect(thread_inc.threadH.elem, SIGNAL(button_pressed()), this, SLOT(next_edit_state()));
    QObject::connect(thread_inc.threadH.elem, SIGNAL(button_long_press()), this, SLOT(close()));

    thread_inc.startOrstopThreadA(); //yellow lamp
    thread_inc.startOrstopThreadC(); //hall_sensor
    thread_inc.startThreadF();       //left button start
    thread_inc.startThreadG();       //right button start
    thread_inc.startThreadH();       //main button start

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
    QObject::connect(this, &MainWindow::send_data_to_dialog, mydialog, &Dialog::setPresentValues);

    //button connections
    QObject::connect(thread_inc.threadF.elem, SIGNAL(button_pressed()), &mydialog->left_button_counter, SLOT(increaseValue()));
    QObject::connect(thread_inc.threadG.elem, SIGNAL(button_pressed()), &mydialog->right_button_counter, SLOT(increaseValue()));
    QObject::connect(thread_inc.threadH.elem, SIGNAL(button_pressed()), &mydialog->main_button_counter, SLOT(increaseValue()));

    //reset trip
    QObject::connect(thread_inc.threadF.elem, SIGNAL(button_long_press()),thread_inc.threadC.elem , SLOT(restart_trip()));
    mydialog->setModal(false);
    mydialog->show();
    mydialog->activateWindow();

    int angle_tmp = ui->speedmeter->getAngle();
    int maxSpeed_tmp = ui->speedmeter->getMax_speed();
    int step_tmp = ui->speedmeter->getStep();
    emit send_data_to_dialog(angle_tmp, maxSpeed_tmp, step_tmp);
}

void MainWindow::on_pushButton_settings_clicked()
{
    startDialog();
}

void MainWindow::next_edit_state()
{
    edit_state = (edit_state + 1) % 3;
    switch (edit_state)
    {
    case 0:
        ui->spinBox_radius->setDisabled(1);
        ui->comboBox->setDisabled(1);
        QObject::disconnect(thread_inc.threadF.elem, SIGNAL(button_long_press()), this, SLOT(start_radius_down()));
        QObject::disconnect(thread_inc.threadF.elem, SIGNAL(stop_long_press()), this, SLOT(stop_radius_down()));
        QObject::disconnect(thread_inc.threadG.elem, SIGNAL(button_long_press()), this, SLOT(start_radius_up()));
        QObject::disconnect(thread_inc.threadG.elem, SIGNAL(stop_long_press()), this, SLOT(stop_radius_up()));
        QObject::disconnect(thread_inc.threadF.elem, SIGNAL(button_pressed()), this, SLOT(prev_unit()));
        QObject::disconnect(thread_inc.threadG.elem, SIGNAL(button_pressed()), this, SLOT(next_unit()));
        QObject::connect(thread_inc.threadF.elem, SIGNAL(button_long_press()),thread_inc.threadC.elem , SLOT(restart_trip()));
        break;
    case 1:
        ui->spinBox_radius->setEnabled(1);
        QObject::connect(thread_inc.threadF.elem, SIGNAL(button_pressed()), ui->spinBox_radius, SLOT(stepDown()));
        QObject::connect(thread_inc.threadG.elem, SIGNAL(button_pressed()), ui->spinBox_radius, SLOT(stepUp()));
        //change radius long presses
        QObject::connect(thread_inc.threadF.elem, SIGNAL(button_long_press()), this, SLOT(start_radius_down()));
        QObject::connect(thread_inc.threadF.elem, SIGNAL(stop_long_press()), this, SLOT(stop_radius_down()));
        QObject::connect(thread_inc.threadG.elem, SIGNAL(button_long_press()), this, SLOT(start_radius_up()));
        QObject::connect(thread_inc.threadG.elem, SIGNAL(stop_long_press()), this, SLOT(stop_radius_up()));

        break;
    case 2:
        ui->spinBox_radius->setDisabled(1);
        ui->comboBox->setEnabled(1);
        QObject::disconnect(thread_inc.threadF.elem, SIGNAL(button_pressed()), ui->spinBox_radius, SLOT(stepDown()));
        QObject::disconnect(thread_inc.threadG.elem, SIGNAL(button_pressed()), ui->spinBox_radius, SLOT(stepUp()));
        QObject::connect(thread_inc.threadF.elem, SIGNAL(button_pressed()), this, SLOT(prev_unit()));
        QObject::connect(thread_inc.threadG.elem, SIGNAL(button_pressed()), this, SLOT(next_unit()));
        //disconnect long presses
        QObject::disconnect(thread_inc.threadF.elem, SIGNAL(button_long_press()), this, SLOT(start_radius_down()));
        QObject::disconnect(thread_inc.threadF.elem, SIGNAL(stop_long_press()), this, SLOT(stop_radius_down()));
        QObject::disconnect(thread_inc.threadG.elem, SIGNAL(button_long_press()), this, SLOT(start_radius_up()));
        QObject::disconnect(thread_inc.threadG.elem, SIGNAL(stop_long_press()), this, SLOT(stop_radius_up()));
        break;
    }
    emit edit_stateChanged(edit_state);
}

void MainWindow::prev_unit()
{
    int unit = ui->comboBox->currentIndex();
    unit = (unit + 2) % 3;
    ui->comboBox->setCurrentIndex(unit);
}

void MainWindow::next_unit()
{
    int unit = ui->comboBox->currentIndex();
    unit = (unit + 1) % 3;
    ui->comboBox->setCurrentIndex(unit);
}

void MainWindow::start_radius_up()
{
    QObject::connect(timer_radius_up, &QTimer::timeout, ui->spinBox_radius,&QSpinBox::stepUp);
    timer_radius_up->start(20);
}

void MainWindow::stop_radius_up()
{
    timer_radius_up->stop();
    QObject::disconnect(timer_radius_up, &QTimer::timeout, ui->spinBox_radius,&QSpinBox::stepUp);
}

void MainWindow::start_radius_down()
{
    QObject::connect(timer_radius_down, &QTimer::timeout, ui->spinBox_radius,&QSpinBox::stepDown);
    timer_radius_down->start(20);
}
void MainWindow::stop_radius_down()
{
    timer_radius_down->stop();
    QObject::disconnect(timer_radius_down, &QTimer::timeout, ui->spinBox_radius,&QSpinBox::stepDown);
}

