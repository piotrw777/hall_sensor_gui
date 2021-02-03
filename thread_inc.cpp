#include "thread_inc.h"
#include "wheel.h"
#include <QDebug>
//#include "ui_mainwindow.h"
#include <iostream>

wheel bike(33);
Thread_Inc::Thread_Inc() : threadA(12), threadB(27), threadC(nullptr)
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

void Thread_Inc::exit()
{
    cout << "Exit";
    threadA.stop();
    threadB.stop();
    threadC.stop();

    threadA.wait();
    threadB.wait();
    threadC.wait();
    cout << "Wyjscie z programu\n";
}
