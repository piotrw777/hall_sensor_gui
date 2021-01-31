#ifndef THREAD_H
#define THREAD_H

#include <iostream>
#include <QObject>
#include <QThread>
#include "led_kit.h"
#include "led.h"

class ThreadBase : public QThread
{
    Q_OBJECT
public:
    ThreadBase(){ running = false; cout << "Pracuje konstruktor domyslny dla ThreadBase\n";};
    bool is_active(){ return running; };

//public slots:
//    void setValue(int val);

//public: signals:
//    void valueChanged(int val);

protected:
    volatile bool running;
};

template <typename Typ>
class Thread : public ThreadBase {

private:
    Typ elem;

public:
    template <typename T>
    Thread(T t) : elem(t) {cout << "Pracuje konstruktor klasy Thread\n";}
    ~Thread(){ elem.off(); }
    void stop()  {
        if(running == false)
        {
            return;
        }
        running = false;
        elem.off();
    }
    void run()  {
        if(running == true)
        {
            cout << "Watek pracuje\n";
            return;
        }
        cout << "Wlanczam watek\n";
        running = true;
        elem.on();
    }
};

//array<led, N> leds  = {16,20,21, 23, 24, 25, 15};
//leds_state<7> kit;
#endif // THREAD_H
