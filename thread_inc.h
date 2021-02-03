#ifndef THREAD_INC_H
#define THREAD_INC_H
#include "thread.h"
#include "led.h"
#include "buzzer.h"
#include "hall_sensor.h"

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

public slots:
    void startThreadB();
    void stopThreadB();
    void startOrstopThreadA();
    void startOrstopThreadB();
    void startOrstopThreadC();
    void exit();
};

#endif // THREAD_INC_H
