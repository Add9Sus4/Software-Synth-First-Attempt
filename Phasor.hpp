//
//  Phasor.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/28/16.
//
//  A Phasor is used to read through the data points of a waveform at a certain rate.

#ifndef Phasor_hpp
#define Phasor_hpp

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "AudioChannel.hpp"
#define SAMPLE_RATE 44100

class Phasor {
private:
    double phase;
    double frequency;
    
public:
    Phasor(double frequency) {
        this->frequency = frequency;
    };
    
    Phasor(double frequency, double initialPhase) {
        this->phase = initialPhase;
        this->frequency = frequency;
    };
    
    double getPhase() { return phase; }
    
    void setPhase(double phase) { this->phase = phase; }
    
    void incrementPhase();
    
    // Set frequency of phasor
    void setFrequency(double frequency) { this->frequency = frequency; }
    
};

#endif /* Phasor_hpp */
