//============================================================================
// Name        : hall_sensor.cpp
//============================================================================
#define DEBUG_INFO 0

#include "hall_sensor.h"
#include "timer.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDebug>
#include <QString>
#include <QVector>

using namespace std;

inline double round_2(double x)
{
    return static_cast<long long>(x * 100)/100.0;
}
inline double round_1(double x)
{
    return static_cast<long long>(x * 10)/10.0;
}
QString QStr_from_msec(double time)
{
    int hours = static_cast<int>(time/3600000.0);
    int minutes = static_cast<int>((time - hours*3600000)/60000.0);
    int seconds = static_cast<int>((time - hours*3600000-minutes*60000)/1000);
    int miliseconds = static_cast<int>(time - hours*3600000-minutes*60000-1000*seconds);

    QString timeStr(8, ' ');
    timeStr[0] = '0'+ hours/10;
    timeStr[1] = '0' + hours % 10;
    timeStr[2] = timeStr[5] = ':';
    timeStr[3] = '0'+ minutes/10;
    timeStr[4] = '0' + minutes % 10;
    timeStr[6] = '0'+ seconds/10;
    timeStr[7] = '0' + seconds % 10;
    return timeStr;
}

hall_sensor::hall_sensor(QObject *parent) : QObject(parent)
{
    pin = 18;
    pinMode(pin,INPUT);
    pi = 3.1415926535;
    radius = 33; //in cm
    unit_number = 0;
    qDebug() << "Promien ustawiony w konstruktorze!!!\n";
    perimeter = 2*pi*radius;
    stop_time = 1500;  //msec
    update_time = 500;  //msec
    update_speed_time = 150; //msc
    delay_time = 1;
    running = false;
    speed_exceded = false;
    speed_limit_value = 16.66;
    unit_number = 0;
    speed_coefficients[0]= 3.6;
    speed_coefficients[1] = 1;
    speed_coefficients[2] = 3.6/1.609344;
    //speed_suffixes = {"km/h", "m/s", "mph"};
    speed_suffixes.push_back("km/h");
    speed_suffixes.push_back("m/s");
    speed_suffixes.push_back("mph");

    distance_coefficients[0] = 0.001;
    distance_coefficients[1] = 1;
    distance_coefficients[2] = 0.0006213727366;
}
void hall_sensor::stopping_function(bool &var_check,bool &is_moving, timer &t_off, timer &t_avg) {
    if(var_check == false) {
        var_check = true;
        t_off.start();
#if(DEBUG_INFO == 1)
        qDebug() << "Starting timer off - magnet closed" << endl;
#endif
    }
    if(is_moving == true && t_off.read_time() > stop_time) {
        is_moving = false;
        speed_exceded = false;
        t_avg.pause();
        emit stop_moving();
        emit speed_change(0);
        emit speed_normal();
        emit rpm_change(0);
#if(DEBUG_INFO == 1)
        qDebug() << "Moving stopped" << endl;
#endif
    }
}
void hall_sensor::on()  {
    running = true;
    int magnet_c = 0; //licznik obrotow
    timer t1;
    timer t_off;
    timer t_avg;
    long long t_avg_pom = -1;
    QString t_avg_string;
    double t_emit = 0;
    double t_speed_emit = 0;
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
            if(static_cast<int>(t_avg.read_time()/100) != t_avg_pom )
            {
                t_avg_pom = static_cast<int>(t_avg.read_time()/100);
                emit time_trip_change(QStr_from_msec(t_avg.read_time()));
            }
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
                t_speed_emit += t;
                speed = velocity(t); //m/s
                rpm = static_cast<int>(60000.0/t);
                distance += get_perimeter();

                //przekroczenie prędkości
                if(speed  >= speed_limit_value && speed_exceded == false) {
                    speed_exceded = true;
                    emit speed_limit_exceed();
                }
                if(speed  < speed_limit_value - 0.2 && speed_exceded == true) {
                    speed_exceded = false;
                    emit speed_normal();
                }
                QString aa(2,'a');
                //update danych na ekran co 1.5 sek
                if(t_emit > update_time) {
                    t_emit = 0;
                    emit average_speed_change(QString::number((distance * 10 *speed_coefficients[unit_number] / t_average),'f',1)); //
                    emit distance_change(QString::number(distance/100*distance_coefficients[unit_number],'f',2)); // w m
                    emit rpm_change(rpm);

                }
                if(t_speed_emit > update_speed_time) {
                    t_speed_emit = 0;
                    emit speed_change(speed*speed_coefficients[unit_number]); //speed w m/s
                }
                //komunikat danych na konsolę
#if(DEBUG_INFO == 1)
                qDebug() << "Magnet detected " << ++magnet_c << " times. " << t/1000 <<" s." << endl <<
                "Velocity: " << speed << " m/s  "<< speed * 3.6 <<" km/h RPM: " << rpm << endl;
#endif
            } // end if(no_magnet == true)
            stopping_function(magnet_post_detection,is_moving, t_off, t_avg);
        } //end if(this->detect())
        else {
            stopping_function(no_magnet,is_moving, t_off, t_avg);
        }  //end else
        delay(delay_time);
    } //end while
}

void hall_sensor::change_unit(int newk)
{
    unit_number = newk;
}

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
