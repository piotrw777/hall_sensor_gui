#include <QDebug>
#include <iostream>
#include "thread_inc.h"

Thread_Inc::Thread_Inc() : threadA(12)
  , threadB(27)  //buzzer
  , threadC(nullptr) //hall_sensor
  , threadD(26)     //blue led
  , threadE(7, vector<int>{16,20,21, 23, 24, 25, 15})
{
    cout << "Pracuje konstruktor domyslny dla Thread_Inc\n";
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
        cout << "ThreadB stops\n";
        threadB.stop();
    }
    else
    {
        cout << "ThreadB starts\n";
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
    cout << "Exit";
    threadA.stop();
    threadB.stop();
    threadC.stop();
    threadD.stop();
    threadE.stop();

    threadA.wait();
    threadB.wait();
    threadC.wait();
    threadD.wait();
    threadE.wait();
    cout << "Wyjscie z programu\n";
}
