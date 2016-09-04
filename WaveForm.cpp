//
//  WaveForm.cpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/28/16.
//
//

#include "WaveForm.hpp"
#include "math.h"

#define PI 3.14159265358979323846264338327950

double WaveForm::getNextSample() {
    int nearestIndex = phasor->getPhase()*(length-1);
    phasor->incrementPhase();
    return (inverted == true) ? samples[nearestIndex]*-1.0f : samples[nearestIndex];
}

// Set frequency of phasor
void WaveForm::setFrequency(double frequency) {
    phasor->setFrequency(frequency);
}