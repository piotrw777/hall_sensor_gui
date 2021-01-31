#ifndef LED_KIT_H
#define LED_KIT_H

#include "led.h"
#include <softPwm.h>
#include <unistd.h>
#include <wiringPi.h>


class led_kit : public leds_state
{

private:
    vector<led> leds;

    double scale_0(double k) {
        return k;
    }

    double scale_1(double k) {
        return k*k/100;
    }

public:
    led_kit(int N, vector<int> vec) : leds_state(N)
    {
        for(int k = 0; k < K; k++) {
            leds.push_back(vec[k]);
            leds[k].prepare_soft_pwm();
        }
    }
    void on();
    void off();
};

void led_kit::on()
{
    for(int k = 0; k < K; k++) {
        softPwmWrite(leds[k].get_pin(), scale_1( Power(k) ));
    }
    next_state();
    delay(100);
}


void led_kit::off()
{
    for(int k = 0; k < K; k++) {
        softPwmWrite(leds[k].get_pin(), 0);
    }
}

//array<led, N> leds  = {16,20,21, 23, 24, 25, 15};

#endif // LED_KIT_H
