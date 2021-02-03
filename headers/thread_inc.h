#ifndef THREAD_INC_H
#define THREAD_INC_H
#include "./headers/thread.h"
#include "./headers/led.h"
#include "./headers/buzzer.h"
#include "./headers/hall_sensor.h"
#include "led_kit.h"

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

public slots:
    void startThreadB();
    void stopThreadB();
    void startThreadD();
    void stopThreadD();

    void startOrstopThreadA();
    void startOrstopThreadB();
    void startOrstopThreadC();
    void startOrstopThreadE();
    void exit();
};

#endif // THREAD_INC_H
