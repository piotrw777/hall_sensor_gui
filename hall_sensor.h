//============================================================================
// Name        : hall_sensor.h
//============================================================================
#ifndef HALL_SENSOR_H
#define HALL_SENSOR_H

#include "element.h"
#include "wheel.h"
#include <QObject>
#include <QString>

class hall_sensor : public QObject {
    Q_OBJECT
private:
    int pin;
    int sooze_time;
    int delay_time;
    double radius;  //w centymetrach
    long double perimeter; //w centymetrach
    double pi;
    bool running;
    double get_perimeter() const{return perimeter;}
    inline double velocity(const double &t) const { return (perimeter * 10)/t; }
    bool detect() const { return !digitalRead(pin); }

public:
    explicit hall_sensor(QObject *parent = nullptr);

signals:
    void speed_change(double);
    void distance_change(double);
    void rpm_change(int);
    void time_trip_change(QString);
    void average_speed_change(double);

public slots:
    void on();
    void off() {running = false;}
};

#endif // HALL_SENSOR_H
