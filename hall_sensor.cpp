//============================================================================
// Name        : hall_sensor.cpp
//============================================================================
#include "hall_sensor.h"
#include "timer.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDebug>
#include <QString>

using namespace std;


inline double round_2(double x)
{
    return static_cast<long long>(x * 100)/100.0;
}
inline double round_1(double x)
{
    return static_cast<long long>(x * 10)/10.0;
}
hall_sensor::hall_sensor(QObject *parent) : QObject(parent)
{
    pin = 18;
    pinMode(pin,INPUT);
    pi = 3.1415926535;
    radius = 33; //in cm
    perimeter = 2*pi*radius;
    sooze_time = 2000;
    delay_time = 1;
    running = false;
    speed_exceded = false;
}

void hall_sensor::on()  {
    running = true;
    double t; //in miliseconds
    int magnet_c = 0; //licznik obrotow
    timer t1;
    timer t_off;
    timer t_abs;
    timer t_avg;
    QString t_avg_string;
    //double prev_sec = 0;
    double t_emit = 0;
    double t_average = 0;  //in miliseconds

    bool stat = false;
    bool no_magnet;
    bool is_moving = false;
    double speed;
    long double distance(0); //in cm
    int rpm;

    cout << "Measure speed start";
    while(running) {

        /*if(is_moving == true && t_abs.read_time()-prev_sec >= 100) {
            emit time_trip_change(round_1(t_average/1000));
            prev_sec = t_abs.read_time();
        }
        */
        if(is_moving == true) {
          t_avg_string = QString::number(t_avg.read_time()/1000, 'f', 2);
          emit time_trip_change(t_avg_string);
        }

        if(this->detect()) {

            //pierwsza detekcja
            if(stat == 0) {

                t1.start();
                t_avg.start();
                t_abs.start();
                stat = 1;
                ++magnet_c;
                no_magnet = false;
                qDebug() << "FIRST MAGNET DETECTION" << endl;
                continue;
            }
            //po przerwie
            if(no_magnet == true) {
                no_magnet = false;
                t1.stop(t);
                if(is_moving == false) {
                    t_avg.resume();
                }
                //przerwa w jeździe
                if(t > sooze_time) {
                    t1.start();
                    t_avg.resume();
                    qDebug() << "Magnet detected " << ++magnet_c << " times. " << endl;
                    continue;
                }
                is_moving = true;
                t_average += t;
                t_emit += t;
                speed = velocity(t);
                rpm = static_cast<int>(60000.0/t);
                distance += get_perimeter();

                if(speed * 3.6 >= 30 && speed_exceded == false) {
                    speed_exceded = true;
                    emit speed_limit_exceed();
                }
                if(speed * 3.6 < 30 && speed_exceded == true) {
                    speed_exceded = false;
                    emit speed_normal();
                }

                if(t_emit > 1500) {
                    t_emit = 0;
                    emit average_speed_change(distance * 36 / t_average);
                    emit distance_change(distance/100000);
                    emit rpm_change(rpm);
                    emit speed_change(speed * 3.6);
                }

                //komunikat na ekran

                qDebug() << "Magnet detected " << ++magnet_c << " times. " << t/1000 <<" s." << endl <<
                "Velocity: " << speed << " m/s  "<< speed * 3.6 <<" km/h RPM: " <<
                rpm << endl;
                t1.start();
            }
        }
        else {
            if(no_magnet == false) {
                t_off.start();
            }
            if(t_off.is_on() == true && t_off.read_time() > 2000) {
                if(is_moving == true) {
                    t_avg.pause();
                }
                emit speed_change(0);
                speed_exceded = false;
                emit speed_normal();
                emit rpm_change(0);
                is_moving = false;
            }
            no_magnet = true;          
        }
        delay(delay_time);
    } //end while
}
