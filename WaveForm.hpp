//
//  WaveForm.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/28/16.
//
//  This class represents a Form of values used to create a repeating waveform.
//  The length of the waveForm can be changed; however, keep in mind that a smaller
//  length means more distortion. 4096 is large enough to ensure distortion remains
//  below audible range, even for a sine wave. Try something like length = 32 though
//  and you'll see what I mean... could be a cool effect for some gritty industrial
//  textures or bass sounds but generally not what you want most of the time.
//
//  WaveForms can be phase-inverted, meaning each value is multiplied by -1, effectively
//  flipping the waveForm upside-down. Thus the SawWaveForm can be used for both increasing
//  and decreasing saw waveforms.
//
//  WaveForms can also be phase-offset by passing in a nonzero value for initialPhase
//  in the constructor, which tells the phasor reading the waveForm to start somewhere in
//  the middle, rather than at the beginning.
//
//--------------------------------------------------------------------------------------------------------------//

#ifndef WaveForm_hpp
#define WaveForm_hpp

#include <stdio.h>
#include "Phasor.hpp"


class WaveForm {
private:
    
    Phasor *phasor;
    
    // The sample index at which the waveForm will begin
    int waveFormStartPosition = 0;
    
protected:
    
    // The number of samples to be stored in the waveForm
    int length;
    
    // Buffer containing the samples in the waveForm
    double *samples = NULL;
    
    // Is the waveForm phase-inverted?
    bool inverted;
    
public:
    
    // Constructor for the waveForm
    WaveForm(double frequency) {
        length = 4096;
        phasor = new Phasor(frequency, WavePhase::FREE);
        initializeWaveForm(length);
        inverted = false;
    };
    
    // Constructor for the waveForm
    WaveForm(double frequency, double initialPhase) {
        length = 4096;
        phasor = new Phasor(frequency, initialPhase, WavePhase::FREE);
        initializeWaveForm(length);
        inverted = false;
    };
    
    void invertPhase() { inverted = true;
    
    
    }
    void restorePhase() { inverted = false; }
    
    // Returns the number of samples in this waveForm
    int getLength() { return length; }
    
    // Populates the samples buffer with values.
    virtual void initializeWaveForm(int length) {};
    
    // Returns the current index at which the waveForm begins.
    int getWaveFormStartPosition() { return waveFormStartPosition; }
    
    // Sets the index at which the waveForm begins.
    void setFormStartPosition(int sampleIndex);
    
    // Returns the next sample
    double getNextSample();
    
    virtual void setPulseWidth(double pulseWidth) {};
    
    // Set frequency of phasor
    void setFrequency(double frequency);
};

#endif /* WaveForm_hpp */