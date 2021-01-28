#ifndef WHEEL_H
#define WHEEL_H

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


#endif // WHEEL_H
