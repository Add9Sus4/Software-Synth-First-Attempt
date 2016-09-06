//
//  PulseWaveForm.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/31/16.
//
//  NOTE: This is not a band-limited waveform; therefore, aliasing will occur at high frequencies.

#ifndef PulseWaveForm_hpp
#define PulseWaveForm_hpp

#include <stdio.h>

#include "WaveForm.hpp"

class PulseWaveForm : public WaveForm {
private:
    double pulseWidth;
public:
    PulseWaveForm();
    PulseWaveForm(double frequency) : WaveForm(frequency) {
        pulseWidth = 0.5;
        initializeWaveForm(length);
    };
    PulseWaveForm(double frequency, double initialPhase) : WaveForm(frequency, initialPhase){
        pulseWidth = 0.5;
        initializeWaveForm(length);
    };
    
    // Populates the samples buffer with values.
    void initializeWaveForm(int length) {
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
    void setPulseWidth(double pulseWidth) {
        this->pulseWidth = pulseWidth;
        initializeWaveForm(length);
    }
};

#endif /* PulseWaveForm_hpp */
