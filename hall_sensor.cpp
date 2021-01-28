#include "hall_sensor.h"
#include "timer.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

void hall_sensor::measure_speed(wheel &vehicle, value &magnet_counter, int sooze_time, int delay_time) {
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
    //cout << "Measure speed start\n";
    while(1) {
        if(this->detect()) {

            //pierwsza detekcja
            if(stat == 0) {
                t1.start();
                stat = 1;
                ++magnet_c;
                no_magnet = false;
                //out << "FIRST MAGNET DETECTION" << endl;
                continue;
            }
            //po przerwie
            if(no_magnet == true) {
                no_magnet = false;
                t1.stop(t);
                //przerwa w jeździe
                if(t > sooze_time) {
                    t1.start();
                    //out << "Magnet detected " << ++magnet_c << " times. " << endl;
                    magnet_counter.setValue(++magnet_c);

                    return; //aby zastopować program
                    continue;
                }
                speed = vehicle.velocity(t);
                rpm = static_cast<int>(60000.0/t);
                distance += vehicle.get_perimeter();

                //komunikat na ekran
                magnet_counter.setValue(++magnet_c);

                //cout << "Magnet detected " << ++magnet_c << " times. " << t/1000 <<" s." << endl <<
                //"Velocity: " << speed << " m/s  "<< speed * 3.6 <<" km/h RPM: " <<
                //rpm << endl;

                t1.start();
            }
        }
        else {
            no_magnet = true;
            t_off.start();
        }
        delay(delay_time);
    } //end while
}
