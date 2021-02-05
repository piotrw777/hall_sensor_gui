//============================================================
// Name        : hall_sensor ON.cpp
//============================================================

void hall_sensor::on()  {
    running = true;
    int magnet_c = 0; //licznik obrotow
    timer t1;
    timer t_off;
    timer t_avg;
    QString t_avg_string;
    double t_emit = 0;
    double t_average = 0;  //in miliseconds

    bool stat = false;
    bool no_magnet;
    bool is_moving = false;

    double t; //in miliseconds
    double speed;
    long double distance(0); //in cm
    int rpm;

    QDebug() << "Measure speed start" << endl;
    while(running) {
        if(is_moving == true) {
          t_avg_string = QString::number(t_avg.read_time()/1000, 'f', 2);
          emit time_trip_change(t_avg_string);
        }

        if(detect()) {
            //pierwsza detekcja
            if(stat == 0) {
                stat = 1;
                no_magnet = false;
                ++magnet_c;
                t1.start();
                t_avg.start();
                qDebug() << "FIRST MAGNET DETECTION" << endl;
                continue;
            }
            //po przerwie
            if(no_magnet == true) {
                no_magnet = false;
                t1.stop(t);
                //przerwa w jeździe
                if(t > sooze_time) {
                    t1.start();
                    //t_avg.resume();
                    qDebug() << "Magnet detected " << ++magnet_c << " times. " << endl;
                    continue;
                }
                if(is_moving == false) {
                    t_avg.resume();
                    emit start_moving();
                    is_moving = true;
                }
                t_average += t;
                t_emit += t;
                speed = velocity(t);
                rpm = static_cast<int>(60000.0/t);
                distance += get_perimeter();

                //przekroczenie prędkości
                if(speed * 3.6 >= 30 && speed_exceded == false) {
                    speed_exceded = true;
                    emit speed_limit_exceed();
                }
                if(speed * 3.6 < 29.8 && speed_exceded == true) {
                    speed_exceded = false;
                    emit speed_normal();
                }
                //update danych na ekran co 1.5 sek
                if(t_emit > 1500) {
                    t_emit = 0;
                    emit average_speed_change(distance * 36 / t_average);
                    emit distance_change(distance/100000);
                    emit rpm_change(rpm);
                    emit speed_change(speed * 3.6);
                }
                //komunikat danych na konsolę
                qDebug() << "Magnet detected " << ++magnet_c << " times. " << t/1000 <<" s." << endl <<
                "Velocity: " << speed << " m/s  "<< speed * 3.6 <<" km/h RPM: " << rpm << endl;

                t1.start();
            } // end if(no_magnet == true)
        } //end if(this->detect())
        else {
            if(no_magnet == false) {
                t_off.start();
                no_magnet = true;
            }
            if(is_moving == true && t_off.read_time() > 1500) {
                is_moving = false;
                peed_exceded = false;
                t_avg.pause();
                emit stop_moving();
                emit speed_change(0);
                emit speed_normal();
                emit rpm_change(0);
            }
        }  //end else
        delay(delay_time);
    } //end while
}
