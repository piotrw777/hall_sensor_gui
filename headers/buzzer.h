#ifndef BUZZER_H
#define BUZZER_H

#include <iostream>
#include "element.h"
#include <wiringPi.h>
#include <QObject>

using namespace std;

class buzzer : public QObject {
    Q_OBJECT
    int pin;
    bool is_on;
    enum buzz_status {ON, OFF, BUZZING};
    buzz_status status;
public:
    buzzer(int pin_) : pin(pin_) {
        cout << "Dziala konstruktor klasy buzzer\n";
        pinMode(pin_, OUTPUT);
        digitalWrite(pin_, 1);
        status = OFF;
    }
    void off()   {
        digitalWrite(pin, 1);
        status = OFF;
    }
    void on()   { // 10 = 1sec
        status = ON;
        while(status != OFF) {
            digitalWrite(pin, 0);
            delay(200);
            digitalWrite(pin, 1);
            delay(200);
        }
        //off();
    }

    void buzz(double t = 1)  {
        on();
        delay(t*100);
        off();
    }
    virtual ~buzzer() {
        cout << "Dziala destruktor klasy buzzer\n";
        digitalWrite(pin, 1);
    }
};

#endif // BUZZER_H
