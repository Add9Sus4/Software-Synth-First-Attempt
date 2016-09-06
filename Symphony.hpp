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
    Symphony(int numVoices) {
        // Check to make sure numVoices is valid
        if (numVoices > MAX_VOICES || numVoices < 1) {
            std::cout << "Invalid value for 'numVoices' (" << numVoices << "). Must be in range 1 - " << MAX_VOICES << "." << std::endl;
            std::cout << "'numVoices' set to " << MAX_VOICES << "." << std::endl;
            numVoices = MAX_VOICES;
        }
        
        // Add all the voices to the vector
        for(int i=0; i<numVoices; i++) {
            voices.push_back(new Voice());
        }

    }
    
    /* Activate a voice - called when a new MIDI note on message is received.
    */
    void activateVoice(double frequency, int noteNumber) {
        // Find the first available voice that isn't activated
        for(std::vector<int>::size_type i = 0; i != voices.size(); i++) {
            
            // If the voice is inactive, use it
            if (voices[i]->isInactive()) { // Inactive voices have noteNumbers of -1
                voices[i]->activate(frequency, noteNumber);
                activeNoteNumbers.push_back(noteNumber); // Add note number to the end of the vector
                return;
            }
        }
        
        /* If this point is reached, no inactive voice was found, meaning all are currently in use
         In this case, find the oldest active voice, deactivate it, and activate this voice */
        
        // Deactivate oldest voice (the one with a note number equal to the one at the front of the activeNoteNumbers vector)
        forceDeactivateVoice(activeNoteNumbers.front());
        
        // Remove the note number of the deactivated voice from the vector
        activeNoteNumbers.erase(activeNoteNumbers.begin());
        
        // Activate the new voice (recursive call)
        activateVoice(frequency, noteNumber);

    }
    
    /* Deactivate a voice with corresponding noteNumber (returns true if voice was
    successfully deactivated) */
    bool deactivateVoice(int noteNumber) {
        // Find the voice associated with the given noteNumber
        for(std::vector<int>::size_type i = 0; i != voices.size(); i++) {
            if (voices[i]->getNoteNumber() == noteNumber) {
                voices[i]->deactivate();
                return true;
            }
        }
        
        // If this point is reached, it means that no voice existed with the specified noteNumber (which should never happen)
        return false;
    }
    
    bool forceDeactivateVoice(int noteNumber) {
        
        // Find the voice associated with the given noteNumber
        for(std::vector<int>::size_type i = 0; i != voices.size(); i++) {
            if (voices[i]->getNoteNumber() == noteNumber) {
                voices[i]->forceDeactivate();
                return true;
            }
        }
        
        // If this point is reached, it means that no voice existed with the specified noteNumber (which should never happen)
        return false;
    }
    
    // Get combined output samples from voices
    double *getSamplesLeft(int blockSize) {
        double *samples = new double[blockSize];
        for (int i=0; i<blockSize; i++) {
            samples[i] = 0.0;
        }
        
        for(std::vector<int>::size_type i = 0; i != voices.size(); i++) {
            double *voiceSamples = voices[i]->getSamplesLeft(blockSize);
            for (int i=0; i<blockSize; i++) {
                samples[i] += voiceSamples[i]/(double)voices.size();
            }
            delete voiceSamples;
        }
        return samples;
    }
    double *getSamplesRight(int blockSize) {
        double *samples = new double[blockSize];
        for (int i=0; i<blockSize; i++) {
            samples[i] = 0.0;
        }
        
        for(std::vector<int>::size_type i = 0; i != voices.size(); i++) {
            double *voiceSamples = voices[i]->getSamplesRight(blockSize);
            for (int i=0; i<blockSize; i++) {
                samples[i] += voiceSamples[i]/(double)voices.size();
            }
            delete voiceSamples;
        }
        return samples;
    }
    
    void changeWaveType(WaveType waveType) {
        for(std::vector<int>::size_type i = 0; i != voices.size(); i++) {
            if (voices[i]->getWaveType() != waveType) {
                voices[i]->changeWaveType(waveType);
                voices[i]->forceDeactivate();
            }
        }
    }
};

#endif /* Symphony_hpp */
