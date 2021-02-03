//============================================================================
// Name        : led_state.cpp
// Author      : Piotr Wasilewski
// Version     : 1
// Copyright   : All rights reserved
// Description : Projekt licznika rowerowego
//============================================================================
#include "./headers/leds_state.h"
#include <vector>

using namespace std;

enum direction {left, right};

void leds_state::next_state() {
    for(int i = 0; i < K; i++) {
        power[i] = power[i] - (power[i] > 0);
    }
    if(peak == K-1) {
        dir = direction::left;
        power[K-2] = M;
        peak = K-2;
    }
    else if(peak == 0) {
        dir = direction::right;
        power[1] = M;
        peak = 1;
    }
    else if(dir == direction::right) {
        power[static_cast<size_t> (peak+1)] = M;
        peak++;
    }
    else if(dir == direction::left) {
        power[static_cast<size_t> (peak-1)] = M;
        peak--;
    }
}

double leds_state::Power(int k) {
    return power[k] * 100.0 / M;
}

leds_state::leds_state(int nr_of_leds) :  K(nr_of_leds)
{
    for(int i = 0; i < K; i++) {
        power.push_back( static_cast<int>(i) );
    }
    dir = direction::left;
    M = K-1;
    peak = K-1;
}

void leds_state::print() {
    for (int i = 0; i < K; i++) {
        cout << power[i] << " ";
    }
    cout << endl;
}

