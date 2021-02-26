#include <QDebug>
#include <iostream>
#include "thread_inc.h"

#define pin_buzzer 27
#define pin_left_button 9
#define pin_right_button 10
#define pin_main_button 11
#define pin_blue_led 26

Thread_Inc::Thread_Inc() : threadA(12)
  , threadB(pin_buzzer)  //buzzer
  , threadC(nullptr) //hall_sensor
  , threadD(pin_blue_led)     //blue led
  , threadE(7, vector<int>{16,20,21, 23, 24, 25, 15})
  , threadF(pin_left_button)
  , threadG(pin_right_button)
  , threadH(pin_main_button)
{
    qDebug() << "Pracuje konstruktor domyslny dla Thread_Inc\n";
}

void Thread_Inc::startThreadB()
{
    threadB.start();
}
void Thread_Inc::stopThreadB()
{
    threadB.stop();
}

void Thread_Inc::startThreadD()
{
    threadD.start();
}
void Thread_Inc::stopThreadD()
{
    threadD.stop();
}
void Thread_Inc::startThreadE()
{
    threadE.start();
}
void Thread_Inc::stopThreadE()
{
    threadE.stop();
}
void Thread_Inc::startThreadF()
{
    qDebug() << "threadF starts";
    threadF.start();
}
void Thread_Inc::stopThreadF()
{
    threadF.stop();
    qDebug() << "threadF stopped";
}
//G
void Thread_Inc::startThreadG()
{
    qDebug() << "threadG starts";
    threadG.start();
}
void Thread_Inc::stopThreadG()
{
    threadG.stop();
    qDebug() << "threadG stopped";
}
//H
void Thread_Inc::startThreadH()
{
    qDebug() << "threadH starts";
    threadH.start();
}
void Thread_Inc::stopThreadH()
{
    threadH.stop();
    qDebug() << "threadH stopped";
}
void Thread_Inc::startOrstopThreadA()
{
    if(threadA.is_active())
    {
        cout << "ThreadA stops\n";
        threadA.stop();
    }
    else
    {
        cout << "ThreadA starts\n";
        threadA.start();
    }
}

void Thread_Inc::startOrstopThreadB()
{
    if(threadB.is_active())
    {
        qDebug()  << "ThreadB stops\n";
        threadB.stop();
    }
    else
    {
        qDebug()  << "ThreadB starts\n";
        threadB.start();
    }
}

void Thread_Inc::startOrstopThreadC()
{
    if(threadC.is_active())
    {
        qDebug() << "ThreadC stops\n";
        threadC.stop();
    }
    else
    {
        qDebug() << "ThreadC starts\n";
        threadC.start();
    }
}

void Thread_Inc::startOrstopThreadE()
{
    if(threadE.is_active())
    {
        qDebug() << "ThreadE stops\n";
        threadE.stop();
    }
    else
    {
        qDebug() << "ThreadE starts\n";
        threadE.start();
    }
}
void Thread_Inc::exit()
{
    qDebug() << "Exit";
    threadA.stop();
    threadB.stop();
    threadC.stop();
    threadD.stop();
    threadE.stop();
    threadF.stop();
    threadG.stop();
    threadH.stop();

    threadA.wait();
    threadB.wait();
    threadC.wait();
    threadD.wait();
    threadE.wait();
    threadF.wait();
    threadG.wait();
    threadH.wait();
    qDebug()  << "All threads stopped";
}
