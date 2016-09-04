//
//  Flanger.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/30/16.
//
//

#ifndef Flanger_hpp
#define Flanger_hpp

#include <stdio.h>
#include "SampleDelay.hpp"
#include "SampleEffect.hpp"
#include "SineWaveForm.hpp"
#include "Oscillator.hpp"

#define FLANGER_MAX_LENGTH  1000
#define FLANGER_MIN_LENGTH  10

class Flanger : public SampleEffect {
    SampleDelay *delay;
    WaveForm *lfo;
    int length;
    double modAmount;
    double frequency;
    double feedback;
    
public:
    Flanger(int length, double modAmount, double frequency, double feedback, WaveType waveType) {
        this->length = length;
        
        // modAmount must be a value between -1.0 and 1.0
        if (modAmount > 1.0 || modAmount < -1.0) {
            modAmount = 0;
        }
        this->modAmount = modAmount;
        this->frequency = frequency;
        
        // Make sure feedback is between 0.99 and 0
        if (feedback > 0.99 || feedback < 0) {
            std::cout << "Feedback was set to " << feedback << ". Feedback must be between 0 and 0.99." << std::endl;
            this->feedback = 0;
        }
        this->feedback = feedback;
        
        // Create a sample delay with twice the length needed (this initializes the buffer with a
        // large enough size to accomodate the lfo fluctuations)
        delay = new SampleDelay(length*2, feedback);
        delay->setLength(this->length);
        lfo = createWaveForm(waveType, frequency);
    }

    double process(double sample);
    WaveForm *createWaveForm(WaveType waveType, double frequency);
    
};

#endif /* Flanger_hpp */
