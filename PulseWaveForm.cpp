//
//  PulseWaveForm.cpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/31/16.
//
//

#include "PulseWaveForm.hpp"

void PulseWaveForm::initializeWaveForm(int length) {
    if (!samples) {
        samples = new double[length];
    }
    int crossover = length/2;
    
    if ((int)((double)length * pulseWidth) < 1) {
        crossover = 1;
    } else if ((int)((double)length * pulseWidth) > length-1) {
        crossover = length-1;
    } else {
        crossover =(int)((double)length*pulseWidth);
    }
    for (int i=0; i<crossover; i++) {
        samples[i] = 1.0;
    }
    for (int i=crossover; i<length; i++) {
        samples[i] = -1.0;
    }
}