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
    Thread<led, 12> threadA;
    Thread<buzzer, 27> threadB;
    Thread<led_kit<7> > threadC;

private slots:
    void startOrstopThreadA();
    void startOrstopThreadB();
    void startOrstopThreadC();
    void exit();
};

#endif // THREAD_INC_H
