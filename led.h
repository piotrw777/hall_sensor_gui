#ifndef LED_H
#define LED_H
#define COMMENTS_LED 0

#include "element.h"

class led : public element {
private:
    static const int PWM_Range = 100;
    bool soft_pwm;
public:
    led(int pin_) : element(pin_), soft_pwm(false) {
        #if(COMMENTS_LED == 1)
        cout << "Dziala konstruktor klasy led\n";
        #endif
        pinMode(pin_, OUTPUT);
    }
    int get_pin() {
        return pin;
    }
    void off() const override {
        digitalWrite(pin, 0);
    }
    void on(int t = 0) const override  {
        digitalWrite(pin, 1);
        if (t == 0) return;
        delay(100 * t);
        this->off();
    }

    virtual ~led() {
        #if(COMMENTS_LED == 1)
        cout << "Dziala destruktor klasy led\n";
        #endif
        if(soft_pwm == false) {
            digitalWrite(pin, 0);
        }
        else {
            softPwmWrite(pin, 0);
        }
    }
    void prepare_soft_pwm() {
        soft_pwm = true;
        int soft_pwm_check;
        soft_pwm_check = softPwmCreate(pin, 0, PWM_Range);
        if (soft_pwm_check != 0) {
            cout << "Soft PWM Error";
            exit(1);
        }
    }
};

#endif // LED.H
