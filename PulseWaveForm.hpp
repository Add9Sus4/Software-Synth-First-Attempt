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
    void initializeWaveForm(int length);
    void setPulseWidth(double pulseWidth) {
        this->pulseWidth = pulseWidth;
        initializeWaveForm(length);
    }
};

#endif /* PulseWaveForm_hpp */
