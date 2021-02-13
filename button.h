#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>
#include <wiringPi.h>

class button : public QObject{
    Q_OBJECT
private:
    int pin;
    bool running;

public:
    button(){}
    button(int _pin): pin(_pin)
        pinMode(_pin, INPUT);
        pullUpDnControl(_pin, PUD_UP);
        running = false;
    }
    ~button(){running = false;}
    bool button_detected(){return digitalRead(pin) == LOW;}
    void on();
    void off(running = false;)

public signals:
    void button_pressed();
};

#endif // LED.H
