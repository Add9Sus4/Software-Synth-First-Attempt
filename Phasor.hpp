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
    Phasor(double frequency, WavePhase wavePhase) {
        this->frequency = frequency;
        setPhase(wavePhase);
    };
    
    Phasor(double frequency, double initialPhase, WavePhase wavePhase) {
        this->phase = initialPhase;
        this->frequency = frequency;
        setPhase(wavePhase);
    };
    
    double getPhase() { return phase; }
    
    void setPhase(WavePhase wavePhase);
    
    void incrementPhase();
    
    // Set frequency of phasor
    void setFrequency(double frequency) { this->frequency = frequency; }
    
};

#endif /* Phasor_hpp */
