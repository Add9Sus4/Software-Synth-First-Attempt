//
//  Symphony.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/1/16.
//
//  A Symphony is a collection of voices

#ifndef Symphony_hpp
#define Symphony_hpp

#define MAX_VOICES  16

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "Voice.hpp"

class Symphony {
private:
    // A vector containing all the voices in the symphony
    std::vector<Voice *> voices;
    
    // A vector containing all the current active notes
    std::vector<int> activeNoteNumbers;
public:
    
    // Create new symphony
    Symphony(int numVoices);
    
    /* Activate a voice - called when a new MIDI note on message is received.
    */
    void activateVoice(double frequency, int noteNumber);
    
    /* Deactivate a voice with corresponding noteNumber (returns true if voice was
    successfully deactivated) */
    bool deactivateVoice(int noteNumber);
    
    bool forceDeactivateVoice(int noteNumber);
    
    // Get combined output samples from voices
    double *getSamplesLeft(int blockSize);
    double *getSamplesRight(int blockSize);
};

#endif /* Symphony_hpp */
