//============================================================================
// Name        : hall_sensor.h
//============================================================================
#ifndef HALL_SENSOR_H
#define HALL_SENSOR_H

#include "element.h"
#include "timer.h"
#include <QVector>
#include <QObject>
#include <QString>

class hall_sensor : public QObject {
    Q_OBJECT
private:
    int pin;
    int stop_time;
    int update_time;
    int update_speed_time;
    int delay_time; //msec
    double radius;  //w centymetrach
    long double perimeter; //w centymetrach
    long double distance; //in cm
    double t_average;  //in miliseconds
    timer t_avg;
    int unit_number;
    double speed_coefficients[3];
    QVector< QString> speed_suffixes;
    double distance_coefficients[3];
    double pi;
    bool running;
    bool speed_exceded;
    double speed_limit_value = 16; //[m/s]
    double get_perimeter() const {return perimeter;}
    inline double velocity(const double &t) const { return (perimeter * 10)/t; } //m/s
    bool detect() const { return !digitalRead(pin); }
    void stopping_function(bool &var_check,bool &is_moving, timer &t_off, timer &t_avg);

public:
    explicit hall_sensor(QObject *parent = nullptr);

signals:
    void speed_change(double);
    //void speed_change(QString);
    void distance_change(QString);
    void rpm_change(int);
    void time_trip_change(QString);
    void time_trip_change(double);
    void average_speed_change(QString);
    void speed_limit_exceed();
    void speed_normal();
    void start_moving();
    void stop_moving();
    void add_to_total_distance(double);

public slots:
    void on();
    void off() {running = false;}
    void change_radius(int r) {radius = r/10.0; perimeter = 2*pi*radius;} //r in mm
    void change_unit(int newk);
    void restart_trip();
};

#endif // HALL_SENSOR_H
