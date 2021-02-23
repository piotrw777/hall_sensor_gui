#include "unitchanger.h"
#include <QTime>

unitChanger::unitChanger(QObject *parent) : QObject(parent)
{
    time_trip = 0;
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
