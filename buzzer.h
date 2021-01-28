#ifndef BUZZER_H
#define BUZZER_H

#include <iostream>
#include "element.h"
#include <wiringPi.h>

using namespace std;

class buzzer : public element {
public:
    buzzer(int pin_) : element(pin_) {
        cout << "Dziala konstruktor klasy buzzer\n";
        pinMode(pin_, OUTPUT);
        digitalWrite(pin_, 1);
    }
    void off() const override {
        digitalWrite(pin, 1);
    }
    void on(int t = 0) const override { // 10 = 1sec
        digitalWrite(pin, 0);
        if(t == 0) return;
        delay(100*t);
        this->off();
    }

    void buzz(double t = 1) {
        this->on();
        delay(t*100);
        this->off();
    }
    virtual ~buzzer() {
        cout << "Dziala destruktor klasy buzzer\n";
        digitalWrite(pin, 1);
    }
};

#endif // BUZZER_H
