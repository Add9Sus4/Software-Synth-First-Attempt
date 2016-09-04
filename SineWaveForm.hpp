//
//  SineWaveForm.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/28/16.
//
//

#ifndef SineWaveForm_hpp
#define SineWaveForm_hpp

#include <stdio.h>
#include "WaveForm.hpp"

class SineWaveForm : public WaveForm {
public:
    SineWaveForm();
    SineWaveForm(double frequency) : WaveForm(frequency){
        initializeWaveForm(length);
    };
    SineWaveForm(double frequency, double initialPhase) : WaveForm(frequency, initialPhase){
        initializeWaveForm(length);
    };
    
    // Populates the samples buffer with values.
    void initializeWaveForm(int length);
};

#endif /* SineWaveForm_hpp */
