//
//  Voice.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/1/16.
//
//  In a polyphonic synthesizer, each individual note is represented by a Voice.

#ifndef Voice_hpp
#define Voice_hpp

#define VOICE_NOT_IN_USE    -1

#include <stdio.h>
#include "OscillatorGroup.hpp"
#include "Envelope.hpp"

class Voice {
private:
    
    // The group of oscillators associated with this voice
    OscillatorGroup *oscillatorGroup;
    
    // The note number associated with this voice
    int noteNumber;
    
    // Amp envelope
    Envelope *ampEnvelopeLeft;
    Envelope *ampEnvelopeRight;
    
public:
    
    // Creates a new voice
    Voice();
    
    // Returns the noteNumber of this voice
    int getNoteNumber() { return noteNumber; }
    
    // Returns true if the voice is currently not in use
    bool isInactive();
    
    // Activates a voice by assigning it an note number and starting all relevant processing (oscillators, lfos, envelopes, etc)
    void activate(double frequency, int noteNumber);
    
    // Deactivates a voice by assigning its noteNumber to VOICE_NOT_IN_USE and stopping all relevant processing (oscillators, lfos, envelopes, etc)
    void deactivate();
    
    void forceDeactivate();
    
    // Returns true if all envelopes are inactive
    bool envIsInactive();
    
    // Get combined output samples from oscillator group
    double *getSamplesLeft(int blockSize);
    double *getSamplesRight(int blockSize);
};

#endif /* Voice_hpp */
