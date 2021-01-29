#ifndef THREAD_H
#define THREAD_H
#include <QObject>
#include <QThread>

#include "led.h"

class Thread : public QThread
{
    Q_OBJECT
public:
    Thread();
    Thread(int pin);

    void stop();
    void run();
    bool is_active(){ return running; };

//public slots:
//    void setValue(int val);

//public: signals:
//    void valueChanged(int val);

private:
    led leddy;
    volatile bool running;
};

#endif // THREAD_H
