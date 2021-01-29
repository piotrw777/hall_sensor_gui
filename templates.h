//============================================================================
// Name        : templates.h
//============================================================================
#ifndef TEMPLATES
#define TEMPLATES
#include <iostream>
#include <array>
#include "softPwm.h"
#include "wiringPi.h"

using namespace std;

class led;

//funkcje odwzorujące przedział [0,100] -> [0,100]
/*
double scale_0(double k) {
    return k;
}

double scale_1(double k) {
    return k*k/100;
}
*/
double scale_0(double k);
double scale_1(double k);

template <size_t K>
class leds_state;

template <size_t N>
void start_blink(const array<led, N> &leds, leds_state<N> &kit, double (*scale_function)(double k) = scale1, int delay_time = 100) {
    for(size_t k = 0; k < N; k++) {
        softPwmWrite(leds[k].pin, scale_function( kit.Power(k)));
    }
    kit.next_state();
    delay(delay_time);
}
void blink(int pin, int delayTime = 10, double (*scale_function)(double k) = scale_1) {
    for (int k = 0; k < 100; k++) {
        softPwmWrite(pin, scale_function(k));
        delay(delayTime);
    }
    for (int k = 0; k < 100; k++) {
        softPwmWrite(pin, scale_function(100-k));
        delay(delayTime);
    }
}
#endif // TEMPLATES
