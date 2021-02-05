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
    stop_time = 1500;  //msec
    delay_time = 1;
    running = false;
    speed_exceded = false;
}
void hall_sensor::stopping_function(bool &var_check,bool &is_moving, timer &t_off, timer &t_avg) {
    if(var_check == false) {
        var_check = true;
        t_off.start();
        qDebug() << "Starting timer off - magnet closed" << endl;
    }
    if(is_moving == true && t_off.read_time() > stop_time) {
        is_moving = false;
        speed_exceded = false;
        t_avg.pause();
        emit stop_moving();
        emit speed_change(0);
        emit speed_normal();
        emit rpm_change(0);
        qDebug() << "Moving stopped" << endl;
    }
}
void hall_sensor::on()  {
    running = true;
    int magnet_c = 0; //licznik obrotow
    timer t1;
    timer t_off;
    timer t_avg;
    QString t_avg_string;
    double t_emit = 0;
    double t_average = 0;  //in miliseconds

    bool stat = false;
    bool no_magnet;
    bool magnet_post_detection;
    bool is_moving = false;

    double t; //in miliseconds
    double speed;
    long double distance(0); //in cm
    int rpm;

    qDebug() << "Measure speed start" << endl;
    while(running) {

        if(is_moving == true) {
          t_avg_string = QString::number(t_avg.read_time()/1000, 'f', 2);
          emit time_trip_change(t_avg_string);
        }

        if(detect()) {
            //pierwsza detekcja
            if(stat == 0) {
                stat = 1;
                no_magnet = false;
                magnet_post_detection = false;
                ++magnet_c;
                t1.start();
                t_avg.start();
                qDebug() << "FIRST MAGNET DETECTION" << endl;
                continue;
            }
            //po przerwie
            if(no_magnet == true) {
                no_magnet = false;
                magnet_post_detection = false;
                t1.stop(t);
                t1.start();
                //przerwa w jeździe
                if(t > stop_time) {
                    t1.start();
                    t_avg.resume();
                    qDebug() << "Detection after pause" << endl
                    << "Magnet detected " << ++magnet_c << " times. " << endl;
                    continue;
                }
                if(is_moving == false) {
                    is_moving = true;
                    t_avg.resume();
                    emit start_moving();
                }
                t_average += t;
                t_emit += t;
                speed = velocity(t);
                rpm = static_cast<int>(60000.0/t);
                distance += get_perimeter();

                //przekroczenie prędkości
                if(speed * 3.6 >= 60 && speed_exceded == false) {
                    speed_exceded = true;
                    emit speed_limit_exceed();
                }
                if(speed * 3.6 < 59.8 && speed_exceded == true) {
                    speed_exceded = false;
                    emit speed_normal();
                }
                //update danych na ekran co 1.5 sek
                if(t_emit > 1500) {
                    t_emit = 0;
                    emit average_speed_change(distance * 36 / t_average);
                    emit distance_change(distance/100000);
                    emit rpm_change(rpm);
                    emit speed_change(speed * 3.6);
                }
                //komunikat danych na konsolę
                qDebug() << "Magnet detected " << ++magnet_c << " times. " << t/1000 <<" s." << endl <<
                "Velocity: " << speed << " m/s  "<< speed * 3.6 <<" km/h RPM: " << rpm << endl;
            } // end if(no_magnet == true)
            stopping_function(magnet_post_detection,is_moving, t_off, t_avg);
        } //end if(this->detect())
        else {
            stopping_function(no_magnet,is_moving, t_off, t_avg);
        }  //end else
        delay(delay_time);
    } //end while
}  //end on function









/*
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
                if(is_moving == false) {
                    emit start_moving();
                }
                is_moving = true;
                t_average += t;
                t_emit += t;
                speed = velocity(t);
                rpm = static_cast<int>(60000.0/t);
                distance += get_perimeter();

                //przekroczenie prędkości
                if(speed * 3.6 >= 30 && speed_exceded == false) {
                    speed_exceded = true;
                    emit speed_limit_exceed();
                }
                if(speed * 3.6 < 29.8 && speed_exceded == true) {
                    speed_exceded = false;
                    emit speed_normal();
                }
                //update danych na ekran co 1.5 sek
                if(t_emit > 1500) {
                    t_emit = 0;
                    emit average_speed_change(distance * 36 / t_average);
                    emit distance_change(distance/100000);
                    emit rpm_change(rpm);
                    emit speed_change(speed * 3.6);
                }

                //komunikat danych na konsolę
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
            if(t_off.is_on() == true && t_off.read_time() > 1500) {
                if(is_moving == true) {
                    t_avg.pause();
                }
                speed_exceded = false;
                emit speed_change(0);
                //speed_exceded = false;
                emit speed_normal();
                emit rpm_change(0);
                if(is_moving == true) {
                    emit stop_moving();
                }
                is_moving = false;
            }
            no_magnet = true;          
        }
        delay(delay_time);
    } //end while
}
*/
