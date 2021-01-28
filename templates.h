//============================================================================
// Name        : templates.h
//============================================================================
#ifndef TEMPLATES
#define TEMPLATES
#include <iostream>
#include <array>
using namespace std;

template <size_t K>
class leds_state;

class led;
//funkcja odwzorująca przedział [0,100] -> [0,100]
double scale_0(double k) {
    return k;
}

double scale_1(double k) {
    return k*k/100;
}
template <size_t N>
void start_blink(const array<led, N> &led, leds_state<N> &kit, double (*f)(double ) = scale_1, int = 100);
/*
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
*/
#endif // TEMPLATES
