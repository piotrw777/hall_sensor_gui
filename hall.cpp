//============================================================================
// Name        : hall.cpp
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <unistd.h>
#include <wiringPi.h>
#include <fstream>
using namespace std;

#define led_pin 12
#define buzz_pin 21
#define hall_pin 18

#define speed_filename "speed_file"
#define rpm_filename "rpm_file"
#define distance_filename "distance_file"

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


class element {
protected:
    int pin;
    static int liczba_elementow;
    element(int pin_): pin(pin_){
        cout << "Dziala konstruktor klasy element\n";
        if(liczba_elementow == 0) {
            if(wiringPiSetupGpio() != 0){
                cout << "Error wiringPiSetupGpio\n";
                exit(1);
            }
            else  {
                cout << "GPIO OK\n";
            }
        }
        liczba_elementow++;
    };
public:
    static int nr_elements()  { return liczba_elementow;}
    virtual void on(int t = 0) {};
    virtual void off() {};
    virtual ~element(){ cout << "Dziala destruktor klasy element\n"; };
};

int element::liczba_elementow = 0;

class led : public element {
public:
    led(int pin_) : element(pin_) {
        cout << "Dziala konstruktor klasy led\n";
        pinMode(pin_, OUTPUT);
    }
    void off() override{
        digitalWrite(pin, 0);
    }
    void on(int t = 0) override{
        digitalWrite(pin, 1);
        if(t == 0) return;
        delay(100*t);
        this->off();
    }

    virtual ~led() {
        cout << "Dziala destruktor klasy led\n";
        digitalWrite(pin, 0);
    }
};

class buzzer : public element {
public:
    buzzer(int pin_) : element(pin_) {
        cout << "Dziala konstruktor klasy buzzer\n";
        pinMode(pin_, OUTPUT);
        digitalWrite(pin_, 1);
    }
    void off() override{
        digitalWrite(pin, 1);
    }
    void on(int t = 0) override{ // 10 = 1sec
        digitalWrite(pin, 0);
        if(t == 0) return;
        delay(100*t);
        this->off();
    }

    void buzz(double t = 1) {
        this->on();
        delay(t*100);
        this->off();
    }
    virtual ~buzzer() {
        cout << "Dziala destruktor klasy buzzer\n";
        digitalWrite(pin, 1);
    }
};
//class hall_sensor;
class wheel {
    //friend class hall_sensor;
    static const double pi;
    double radius;  //w centymetrach
    long double perimeter; //w centymetrach

public:
    wheel(double radius) : radius(radius){perimeter = 2*pi*radius;}
    double get_perimeter() {return perimeter;}
    inline double velocity(const double &t) { return (perimeter * 10)/t; } //w m/s
};
const double wheel::pi = 3.141592;

class hall_sensor : public element {
public:
    hall_sensor(int pin_) : element(pin_) {
        pinMode(pin_,INPUT);
    }
    bool detect() {
        return !digitalRead(pin);
    }

    void measure_speed(wheel &vehicle, ostream &out, ostream &speed_out,ostream &rpm_out, ostream &distance_out,  int sooze_time = 2000, int delay_time = 1);

};
void hall_sensor::measure_speed(wheel &vehicle, ostream &out,ostream &speed_out,ostream &rpm_out, ostream &distance_out, int sooze_time,int delay_time) {
    double t;
    int magnet_c = 0; //licznik
    timer t1;
    timer t_average;
    timer t_off;
    bool stat = false;
    bool no_magnet;
    double speed;
    long double distance(0);
    int rpm; 
    
    out << "CHECK\n";

    while(1) {
        if(this->detect()) {

            //pierwsza detekcja
            if(stat == 0) {
                t1.start();
                stat = 1;
                ++magnet_c;
                no_magnet = false;
                out << "FIRST MAGNET DETECTION" << endl;
                continue;
            }
            //po przerwie
            if(no_magnet == true) {
                no_magnet = false;
                t1.stop(t);
                //przerwa w jeździe
                if(t > sooze_time) {
                    t1.start();
                    out << "Magnet detected " << ++magnet_c << " times. " << endl;
                    return; //aby zastopować program
                    continue;
                }
                speed = vehicle.velocity(t);
                rpm = static_cast<int>(60000.0/t);
                distance += vehicle.get_perimeter();
                
                //komunikat na ekran
                out << "Magnet detected " << ++magnet_c << " times. " << t/1000 <<" s." << endl <<
                "Velocity: " << speed << " m/s  "<< speed * 3.6 <<" km/h RPM: " <<
                rpm << endl;
                
                //writing values to files
                speed_out << speed << endl;
                rpm_out << rpm << endl;
                distance_out << distance << endl;
                t1.start();
            }
        }
        else {
            no_magnet = true;
            t_off.start();

        }
        delay(delay_time);
    } //end while


}//end measure_speed

int main(void) {

    led yellow(led_pin);
    yellow.on(3);
    
    hall_sensor hally(hall_pin);
    wheel bike(33);
    hally.measure_speed(bike, cout, speed_file, rpm_file, distance_file);
    cout << "KONIEC PROGRAMU\n";
    
    //buzzer loudy(buzz_pin);
    //loudy.off();

}
