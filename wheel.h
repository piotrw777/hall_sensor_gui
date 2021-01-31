//============================================================================
// Name        : wheel.h
// Author      : Piotr Wasilewski
// Version     : 1
// Copyright   : All rights reserved
// Description : Projekt licznika rowerowego
//============================================================================
#ifndef WHEEL_H
#define WHEEL_H

class wheel {
    //friend class hall_sensor;
    static const double pi;
    double radius;  //w centymetrach
    long double perimeter; //w centymetrach

public:
    wheel(){}
    wheel(double radius) : radius(radius){perimeter = 2*pi*radius;}
    wheel(const wheel &w) {
        radius = w.radius;
    }
    double get_perimeter() const{return perimeter;}
    inline double velocity(const double &t) const { return (perimeter * 10)/t; } //w m/s
};

#endif // WHEEL_H
