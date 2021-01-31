#ifndef THREAD_INC_H
#define THREAD_INC_H
#include "thread.h"
#include "led.h"
#include "buzzer.h"
#include "led_kit.h"

class Thread_Inc : public QObject
{
    friend class MainWindow;
    Q_OBJECT
public:
    Thread_Inc();

private:
    Thread<led> threadA;
    Thread<buzzer> threadB;
    Thread<led > threadC;

private slots:
    void startOrstopThreadA();
    void startOrstopThreadB();
    void startOrstopThreadC();
    void exit();
};

#endif // THREAD_INC_H
