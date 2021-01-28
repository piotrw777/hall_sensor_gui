#ifndef ELEMENT_H
#define ELEMENT_H
#define COMMENTS_ELEMENT 0

#include <iostream>
#include "wiringPi.h"
#include "softPwm.h"

using namespace std;

class element {
protected:
    int pin;
    static int liczba_elementow;
    element(int pin_): pin(pin_){
        #if(COMMENTS_ELEMENT == 1)
        cout << "Dziala konstruktor klasy element\n";
        #endif
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
    }
    element() {
        #if(COMMENTS_ELEMENT == 1)
        cout << "Dziala konstruktor domyslny klasy element\n";
        #endif
        liczba_elementow++;
    }

public:
    static int nr_elements() { return liczba_elementow;}
    virtual void on(int  = 0) const {}
    virtual void off() const {}
    virtual ~element(){ 
        #if(COMMENTS_ELEMENT == 1)
        cout << "Dziala destruktor klasy element\n"; 
        #endif
    }
};


#endif
