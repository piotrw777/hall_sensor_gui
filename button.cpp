#include <button.h>
#include <wiringPi.h>

void button::on() {
    running = true;
    bool button_released = true;

    while(running){
        if(button_released == true && button_detected() == true) {
            button_released = false;
            emit button_pressed();
        }
        else if(button_detected() == false) {
            button_released = true;
        }
        delay(1);
    }
}


