//
//  Flanger.cpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/30/16.
//
//

#include "Flanger.hpp"

double Flanger::process(double sample) {
    double newSample = sample;
    
    // Set new length of delay based on lfo, mod amount
    int newLength = length + lfo->getNextSample()*(length*modAmount);
    
    // Make sure length is at least 2, otherwise delay will be too short at bottom of lfo range
    if (newLength < 2) newLength = 2;
    
    // Set new delay length
    delay->setLength(newLength);
    
    // Process sample with delay
    newSample = delay->process(newSample);
    
    // Return processed sample
    return newSample;
}

