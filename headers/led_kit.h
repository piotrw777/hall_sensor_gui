#ifndef LED_KIT_H
#define LED_KIT_H

#include "led.h"
#include <softPwm.h>
#include <unistd.h>
#include <wiringPi.h>
#include "leds_state.h"

class led_kit : public leds_state
{

private:
    enum led_kit_status {ON, OFF};
    led_kit_status status;
    vector<led> leds;

    inline double scale_0(double k) {
        return k;
    }

    inline double scale_1(double k) {
        return k*k/100;
    }

public:
    led_kit(int N, vector<int> vec);

    void on();
    void off();
};





//array<led, N> leds  = {16,20,21, 23, 24, 25, 15};

#endif // LED_KIT_H
