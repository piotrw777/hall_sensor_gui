#ifndef LEDS_STATE_H
#define LEDS_STATE_H

#include <iostream>
#include <vector>
#include "./headers/led.h"

using namespace std;

class leds_state{

private:
    enum direction {left, right};
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
