//
//  Oscillator.cpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/28/16.
//
//

#include "Oscillator.hpp"
#include <math.h>

double *Oscillator::getSamplesLeft(int blockSize) {
    if (pan > 1.0) {
        std::cout << "Pan was equal to " << pan << ", must be between -1.0 and 1.0. Set to 1.0." << std::endl;
        pan = 1.0;
    }
    if (pan < -1.0) {
        std::cout << "Pan was equal to " << pan << ", must be between -1.0 and 1.0. Set to -1.0." << std::endl;
        pan = -1.0;
    }
    
    double panFactor = fabs(0.0f - pan)*(0.708 - 1.0) + 1.0;
    
    double *samples = new double[blockSize];
    for (int i=0; i<blockSize; i++) {
        samples[i] = waveFormLeft->getNextSample()*panFactor*fabs(pan - 1.0f)/2.0;
    }
    return samples;
}

double *Oscillator::getSamplesRight(int blockSize) {
    
    double panFactor = fabs(0.0f - pan)*(0.708 - 1.0) + 1.0;
    
    double *samples = new double[blockSize];
    for (int i=0; i<blockSize; i++) {
        samples[i] = waveFormRight->getNextSample()*panFactor*fabs(pan + 1.0f)/2.0;
    }
    return samples;
}

void Oscillator::setPulseWidth(double pulseWidth) {
    if (waveType == WaveType::PULSE) {
        waveFormLeft->setPulseWidth(pulseWidth);
        waveFormRight->setPulseWidth(pulseWidth);
    }
}

void Oscillator::setFrequency(double frequency) {
    this->frequency = frequency;
    waveFormLeft->setFrequency(frequency);
    waveFormRight->setFrequency(frequency);
}