#ifndef THREAD_H
#define THREAD_H

#include <iostream>
#include <QObject>
#include <QThread>
#include "./headers/led.h"

class ThreadBase : public QThread
{
    Q_OBJECT
public:
    ThreadBase(){ running = false; cout << "Pracuje konstruktor domyslny dla ThreadBase\n";};
    bool is_active(){ return running; };

protected:
    volatile bool running;
};

template <typename Typ>
class Thread : public ThreadBase {

public:
    Typ *elem;
    Thread() : elem(nullptr) {cout << "Pracuje konstruktor klasy Thread\n";}

    template<typename T>
    Thread(T t) {elem = new Typ(t);}

    template<typename T1, typename T2>
    Thread(T1 t1, T2 t2) {elem = new Typ(t1, t2);}

    ~Thread(){ elem->off(); delete elem;}
    void stop()  {
        if(running == false)
        {
            return;
        }
        running = false;
        elem->off();
    }
    void run()  {
        if(running == true)
        {
            cout << "Watek pracuje\n";
            return;
        }
        cout << "Wlanczam watek\n";
        running = true;
        elem->on();
    }
};

//array<led, N> leds  = {16,20,21, 23, 24, 25, 15};
//leds_state<7> kit;
#endif // THREAD_H
