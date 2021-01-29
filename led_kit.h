#ifndef LED_KIT_H
#define LED_KIT_H
#include "leds_state.h"
#include "led.h"
#include <softPwm.h>
#include <wiringPi.h>

template <size_t N>
class led_kit : public leds_state<N>
{
private:
    array<led, N> leds;

    double scale_0(double k) {
        return k;
    }

    double scale_1(double k) {
        return k*k/100;
    }

public:
    led_kit(array<int, N> arr)
    {
        leds = arr;
        for(int k = 0; k < N; k++) {
            leds[k].prepare_soft_pwm();
        }
    }
    void on();
    void off();
};

template <size_t N>
void led_kit<N>::on()
{
    for(size_t k = 0; k < N; k++) {
        softPwmWrite(leds[k].pin, scale_function( Power(k)));
    }
    next_state();
    delay(100);
}

template <size_t N>
void led_kit<N>::off()
{
    for(size_t k = 0; k < N; k++) {
        softPwmWrite(leds[k].pin, 0);
    }
}

//array<led, N> leds  = {16,20,21, 23, 24, 25, 15};

#endif // LED_KIT_H
