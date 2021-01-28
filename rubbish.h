#ifndef RUBBISH_H
#define RUBBISH_H
/*
 * #include <iostream>
#include <vector>
#include <string>
#include <chrono>
//#include <unistd.h>
#include <wiringPi.h>
#include <fstream>
#include "element.h"
#include "led.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
void * thread_function_1(void *) {
    for(int k = 0; k < 10; k++) {
        digitalWrite(led_pin, 1);
        delay(1000);
        digitalWrite(led_pin, 0);
        delay(1000);
    }
    return nullptr;
}

void * thread_function_2(void *) {
    for(int k = 0; k < 10; k++) {
        digitalWrite(led_pin2, 1);
        delay(1000);
        digitalWrite(led_pin2, 0);
        delay(1000);
    }
    return nullptr;
}


    pthread_t thr1;
    pthread_t thr2;

    pthread_create(&thr1, NULL, thread_function_1, NULL);
    pthread_create(&thr2, NULL, thread_function_2, NULL);

    pthread_join(thr1, NULL);
    pthread_join(thr2, NULL);

*/
#endif // RUBBISH_H
