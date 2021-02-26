#ifndef THREAD_INC_H
#define THREAD_INC_H

#include "thread.h"
#include "led.h"
#include "buzzer.h"
#include "hall_sensor.h"
#include "led_kit.h"
#include "button.h"

class MainWindow;

class Thread_Inc : public QObject
{
    friend class MainWindow;
    Q_OBJECT
public:
    Thread_Inc();
    ~Thread_Inc(){exit();}

private:
    Thread<led> threadA;
    Thread<buzzer> threadB;
    Thread<hall_sensor> threadC;
    Thread<led> threadD;
    Thread<led_kit> threadE;
    Thread<button> threadF; //button left
    Thread<button> threadG; //button right
    Thread<button> threadH; //button main

public slots:
    void startOrstopThreadA();
    void startOrstopThreadB();
    void startThreadB();
    void stopThreadB();
    void startOrstopThreadC();
    void startThreadD();
    void stopThreadD();
    void startThreadE();
    void stopThreadE();
    void startOrstopThreadE();
    void startThreadF();
    void stopThreadF();
    void startThreadG();
    void stopThreadG();
    void startThreadH();
    void stopThreadH();

    void exit();
};

#endif // THREAD_INC_H
