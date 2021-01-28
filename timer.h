#ifndef TIMER_H
#define TIMER_H

#include <chrono>

using namespace std;

typedef chrono::_V2::steady_clock::time_point chrono_t;

enum timer_status {OFF, ON};

class timer {
    chrono_t _start;
    chrono_t _end;
    double _time = 0;
    timer_status status = OFF;
public:
    void start() {
        _start = chrono::steady_clock::now();
        status = ON;
    }
    void stop() {
        _end = chrono::steady_clock::now();
        _time = chrono::duration_cast<chrono::milliseconds>(_end - _start).count();
        status = OFF;
    }
    template <typename T>
    void stop(T &t) {
        _end = chrono::steady_clock::now();
        _time = chrono::duration_cast<chrono::milliseconds>(_end - _start).count();
        t = _time;
        status = OFF;
    }
    void restart() {
        _start = chrono::steady_clock::now();
    }
    double get_time() {return _time;}

    double read_time() {
        chrono_t end_pom = chrono::steady_clock::now();
        return chrono::duration_cast<chrono::milliseconds>(end_pom - _start).count();
    }
    bool is_on() {return status;}
};
#endif // TIMER_H
