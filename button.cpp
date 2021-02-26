#include <button.h>
#include <wiringPi.h>
#include <QDebug>

void myInterrupt()
{
    qDebug() << "Pressed!";
}

button::button(int _pin): pin(_pin){
    qDebug() << "Konstruktor jednoargumentowy button";
    pinMode(_pin, INPUT);
    pullUpDnControl(_pin, PUD_UP);

//    if(wiringPiISR(_pin, INT_EDGE_FALLING, &myInterrupt) < 0)
//    {
//        printf("Unable to setup interrupt handler!\r\n");
//    }
    running = false;
}

void button::on() {
    qDebug() << "Button on";
    running = true;
    bool button_released = true;

    while(running){
        if(button_released == true && button_detected() == true) {
            button_released = false;
            qDebug() << "Button pressed";
            emit button_pressed();
        }
        else if(button_detected() == false) {
            button_released = true;
        }
        delay(3);
    }
}
