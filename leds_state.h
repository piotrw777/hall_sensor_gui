#ifndef LEDS_STATE_H
#define LEDS_STATE_H

#include <iostream>
#include <vector>
#include "led.h"

using namespace std;

enum direction;

class leds_state{

private:

    int M; //max power
    int peak;
    direction dir;
protected:
    void next_state();
    double Power(int k);

    int K; // number of leds
    vector<int> power;

public:
    leds_state(int nr_of_leds);

    void print();
};

#endif
