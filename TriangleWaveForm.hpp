//
//  TriangleWaveForm.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/28/16.
//
//  NOTE: This is not a band-limited waveform; therefore, aliasing will occur at high frequencies.

#ifndef TriangleWaveForm_hpp
#define TriangleWaveForm_hpp

#include <stdio.h>
#include "WaveForm.hpp"

class TriangleWaveForm : public WaveForm {
public:
    TriangleWaveForm();
    TriangleWaveForm(double frequency) : WaveForm(frequency){
        initializeWaveForm(length);
    };
    TriangleWaveForm(double frequency, double initialPhase) : WaveForm(frequency, initialPhase){
        initializeWaveForm(length);
    };
    
    // Populates the samples buffer with values.
    void initializeWaveForm(int length);
};

#endif /* TriangleWaveForm_hpp */
