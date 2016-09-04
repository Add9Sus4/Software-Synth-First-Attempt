//
//  NoiseWaveForm.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/28/16.
//
//  NOTE: This is not a band-limited waveform; therefore, aliasing will occur at high frequencies.

#ifndef NoiseWaveForm_hpp
#define NoiseWaveForm_hpp

#include <stdio.h>
#include "WaveForm.hpp"

class NoiseWaveForm : public WaveForm {
public:
    NoiseWaveForm();
    NoiseWaveForm(double frequency) : WaveForm(frequency){
        initializeWaveForm(length);
    };
    NoiseWaveForm(double frequency, double initialPhase) : WaveForm(frequency, initialPhase){
        initializeWaveForm(length);
    };
    
    // Populates the samples buffer with values.
    void initializeWaveForm(int length);
};

#endif /* NoiseWaveForm_hpp */
