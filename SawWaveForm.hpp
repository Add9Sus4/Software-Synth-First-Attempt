//
//  SawWaveForm.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/28/16.
//
//  NOTE: This is not a band-limited waveform; therefore, aliasing will occur at high frequencies.

#ifndef SawWaveForm_hpp
#define SawWaveForm_hpp

#include <stdio.h>
#include "WaveForm.hpp"

class SawWaveForm : public WaveForm {
public:
    SawWaveForm();
    SawWaveForm(double frequency) : WaveForm(frequency){
        initializeWaveForm(length);
    };
    SawWaveForm(double frequency, double initialPhase) : WaveForm(frequency, initialPhase){
        initializeWaveForm(length);
    };
    
    // Populates the samples buffer with values.
    void initializeWaveForm(int length) {
        samples = new double[length];
        for (int i=0; i<length; i++) {
            samples[i] = -1.0 + 2.0*i/(double)length;
        }
    }
};

#endif /* SawWaveForm_hpp */
