//
//  LFO.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/22/16.
//
//

#ifndef LFO_hpp
#define LFO_hpp

#include <stdio.h>

#include "Modulator.hpp"
#include "Oscillator.hpp"
#include "WaveForm.hpp"

class LFO : public Modulator {
    WaveForm* waveForm;
public:
    LFO() {
        LFO(1.0);
    }
    LFO(double frequency) {
        waveForm = new SineWaveForm(frequency);
    }
    double modulate(double value) {
        return value + 400.0*waveForm->getNextSample();
    }
};

#endif /* LFO_hpp */
