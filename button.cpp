#include <button.h>
#include <wiringPi.h>
#include <QDebug>

button::button(int _pin): pin(_pin), pressed(false), long_press(false) {
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
    pressed = false;
    long_press = false;
//  bool button_released = true;

//    while(running){
//        if(button_released == true && button_detected() == true) {
//            button_released = false;
//            qDebug() << "Button pressed";
//            emit button_pressed();
//        }
//        else if(button_detected() == false) {
//            button_released = true;
//        }
//        delay(3);
//    }
    while(running) {
        if(button_detected()) {
            if(pressed == false) {
                pressed = true;
                tpress1.start();
                continue;
            }
            if(pressed == true && long_press == false && tpress1.read_time() > 500) {
                long_press = true;
                emit button_long_press();
                qDebug() << "Button long pressed";
            }
        }
        else if(pressed == true && button_detected() == false){
            pressed = false;
            if(long_press == true) {
                long_press = false;
                emit stop_long_press();
                qDebug() << "Button long press released";
            }
            else {
                emit button_pressed();
                qDebug() << "Button pressed";
            }
        }
        delay(3);
    }
}
