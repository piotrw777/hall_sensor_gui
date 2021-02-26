#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>
#include <QDebug>
#include <wiringPi.h>
#include "timer.h"

/*
 * #include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <unistd.h>
#include <iostream>
*/

class button : public QObject {
    Q_OBJECT

private:
    int pin;
    bool running;
    bool pressed;
    bool long_press;
    timer tpress1;

public:
    button(){}
    button(int);

    ~button(){running = false;}
    bool button_detected(){return digitalRead(pin) == HIGH;}
    void on();
    void off(){running = false;}

signals:
    void button_pressed();
    void button_long_press();
    void stop_long_press();
};

#endif // LED.H
