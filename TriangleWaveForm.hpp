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
    void initializeWaveForm(int length) {
        samples = new double[length];
        for (int i=0; i<length/4; i++) {
            samples[i] = 0.0 + 1.0*4*i/(double)length;
        }
        for (int i=length/4; i<length/2; i++) {
            samples[i] = 1.0 - 1.0*4*(i - length/4)/(double)length;
        }
        for (int i=length/2; i<length*3/4; i++) {
            samples[i] = 0.0 - 1.0*4*(i - length/2)/(double)length;
        }
        for (int i=length*3/4; i<length; i++) {
            samples[i] = -1.0 + 1.0*4*(i - length*3/4)/(double)length;
        }
    }
};

#endif /* TriangleWaveForm_hpp */
