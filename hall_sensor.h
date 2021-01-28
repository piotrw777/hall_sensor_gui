#ifndef HALL_SENSOR_H
#define HALL_SENSOR_H

#include "element.h"
#include "wheel.h"
#include "value.h"

class MainWindow;

class hall_sensor : public element {

public:
    hall_sensor() {};
    hall_sensor(int pin_) : element(pin_) {
        pinMode(pin_,INPUT);
    }
    bool detect() {
        return !digitalRead(pin);
    }

    void measure_speed(wheel &vehicle, value &magnet_counter, int sooze_time = 2000, int delay_time = 1);
};

#endif // HALL_SENSOR_H
