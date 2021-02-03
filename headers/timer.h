//============================================================================
// Name        : timer.h
//============================================================================
#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <QObject>

using namespace std;

typedef chrono::_V2::steady_clock::time_point chrono_t;

class timer : public QObject{
    Q_OBJECT

    enum timer_status {OFF, ON, PAUSED};
    chrono_t _start;
    chrono_t _end;
    double _time;
    timer_status status;
public:
    timer() : _time(0) {status = OFF;}

    template <typename T>
    void stop(T &t) {
        status = OFF;
        _end = chrono::steady_clock::now();
        _time += chrono::duration_cast<chrono::milliseconds>(_end - _start).count();
        t = _time;
    }
public slots:
    void start() {
        status = ON;
        _time = 0;
        _start = chrono::steady_clock::now();

    }
    void stop() {
        status = OFF;
        _end = chrono::steady_clock::now();
        _time += static_cast<double>(chrono::duration_cast<chrono::milliseconds>(_end - _start).count());
    }
    void restart() {
         status = ON;
        _time = 0;
        _start = chrono::steady_clock::now();
    }
    void pause() {
        status = PAUSED;
        _end = chrono::steady_clock::now();
        _time += static_cast<double>(chrono::duration_cast<chrono::milliseconds>(_end - _start).count());
    }
    void resume() {
        status = ON;
        _start = chrono::steady_clock::now();
    }
    double get_time() {return _time;}

    double read_time() {
        if(status == OFF || status == PAUSED) return _time;
        chrono_t end_pom = chrono::steady_clock::now();
        return _time + static_cast<double>(chrono::duration_cast<chrono::milliseconds>(end_pom - _start).count());
    }
    timer_status get_status() {return status;}

    bool is_on() {return status == ON;}
};
#endif // TIMER_H
