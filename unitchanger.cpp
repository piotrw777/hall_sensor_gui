#include "unitchanger.h"
#include <QTime>
#include <QString>

unitChanger::unitChanger(QObject *parent) : QObject(parent)
{
    unitNumber = 0;
    speed_coefficients = {3.6, 1, 3.6/1.609344};
    distance_coefficients = {0.001, 1, 0.0006213727366};
    speed_suffixes = {"km/h", "m/s", "mph"};
    distance_suffixes = {"km", "m", "mi"};
    time_trip = 0;
    speed = 0;
}

double unitChanger::get_speed_unit()
{
    return speed_coefficients[unitNumber];
}

double unitChanger::get_distance_units()
{
    return distance_coefficients[unitNumber];
}

QString unitChanger::get_speed_suffix()
{
    return speed_suffixes[unitNumber];
}

QString unitChanger::get_distance_suffix()
{
    return distance_suffixes[unitNumber];
}

void unitChanger::time_trip_change(double time)
{
    if(time != time_trip) {
        time_trip = time;
        int hours = static_cast<int>(time/3600000.0);
        int minutes = static_cast<int>((time - hours*3600000)/60000.0);
        int seconds = static_cast<int>((time - hours*3600000-minutes*60000)/1000);
        int miliseconds = static_cast<int>(time - hours*3600000-minutes*60000-1000*seconds);

        QTime timeq(hours, minutes, seconds, miliseconds);
        //QString timeStr = timeq.toString("hh:mm%ss#zzz");
        QString timeStr(10, ' ');
        timeStr[0] = '0'+ hours/10;
        timeStr[1] = '0' + hours % 10;
        timeStr[2] = timeStr[5] = timeStr[8] = ':';
        timeStr[3] = '0'+ minutes/10;
        timeStr[4] = '0' + minutes % 10;
        timeStr[6] = '0'+ seconds/10;
        timeStr[7] = '0' + seconds % 10;
        timeStr[9] = '0'+ miliseconds/100;

        emit time_trip_change(timeStr);
    }
}

void unitChanger::change_unitNumber(int newNr)
{
    unitNumber = newNr;
}
void unitChanger::speed_change(double speed_hall)
{
    if(speed_hall != speed) {
        QString speedStr = QString::number(speed_hall*speed_coefficients[unitNumber],'f',1);
        speed = speed_hall;
        emit speed_change(speedStr);
    }
}
