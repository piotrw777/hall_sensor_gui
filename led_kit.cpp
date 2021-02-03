#include "led_kit.h"
#include <softPwm.h>

led_kit::led_kit(int N, vector<int> vec) : leds_state(N)
{
    for(int k = 0; k < K; k++) {
        leds.push_back(vec[k]);
        leds[k].prepare_soft_pwm();
    }
}

void led_kit::on()
{
    status = ON;
    while(status != OFF) {
        for(int k = 0; k < K; k++) {
            softPwmWrite(leds[k].get_pin(), scale_1( Power(k) ));
        }
        next_state();
        delay(100);
    }
    if(status == OFF) {
        off();
    }
}

void led_kit::off()
{
    status = OFF;
    for(int k = 0; k < K; k++) {
        softPwmWrite(leds[k].get_pin(), 0);
    }
}
