#include "thread_inc.h"
//#include "ui_mainwindow.h"
#include <iostream>

using namespace std;
/*
 *
 *
 * template <typename Typ1, size_t N1, typename Typ2, size_t N2, typename Typ3, size_t N3>
class Thread_Inc : public QObject
{
    friend class MainWindow;
    Q_OBJECT
public:
    Thread_Inc();

private:
    Thread<Typ1, N1> threadA;
    Thread<Typ2, N2> threadB;
    Thread<Typ3, N3> threadC;

private slots:
    void startOrstopThreadA();
    void startOrstopThreadB();
    void startOrstopThreadC();
    void exit();
};
*/

Thread_Inc::Thread_Inc() :
    threadA(), threadB(), threadC()
{
    cout << "Pracuje konstruktor domyslny dla Thread_Inc\n";
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
        cout << "ThreadC stops\n";
        threadC.stop();
    }
    else
    {
        cout << "ThreadC starts\n";
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
