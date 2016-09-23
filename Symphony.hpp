//
//  Symphony.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/1/16.
//
//  A Symphony is a collection of voices

#ifndef Symphony_hpp
#define Symphony_hpp

#define MAX_VOICES              16
#define GAIN_CHANGE_LENGTH      25

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "Voice.hpp"

class Symphony {
private:
    // A vector containing all the voices in the symphony
    std::vector<Voice *> voices;
    
    int g_attack;
    int g_decay;
    double g_sustain;
    int g_release;
    
    int g_filter_attack;
    int g_filter_decay;
    double g_filter_sustain;
    int g_filter_release;
    
    double gain;
    double gainChangeIncrement;
    int gainChangeCount;
    bool changingGain;
    
public:
    
    // Create new symphony
    Symphony(int numVoices) {
        
        g_attack = g_filter_attack = ATTACK_DEFAULT;
        g_decay = g_filter_decay = DECAY_DEFAULT;
        g_sustain = g_filter_sustain = SUSTAIN_DEFAULT;
        g_release = g_filter_release = RELEASE_DEFAULT;
        
        gain = 1.0;
        
        gainChangeIncrement = 0.0;
        gainChangeCount = 0;
        
        changingGain = false;
        
        // Check to make sure numVoices is valid
        if (numVoices > MAX_VOICES || numVoices < 1) {
            std::cout << "Invalid value for 'numVoices' (" << numVoices << "). Must be in range 1 - " << MAX_VOICES << "." << std::endl;
            std::cout << "'numVoices' set to " << MAX_VOICES << "." << std::endl;
            numVoices = MAX_VOICES;
        }
        
        // Add all the voices to the vector
        for(int i=0; i<numVoices; i++) {
            voices.push_back(new Voice(g_attack, g_decay, g_sustain, g_release, g_filter_attack, g_filter_decay, g_filter_sustain, g_filter_release));
        }

    }
    
    /* Activate a voice - called when a new MIDI note on message is received.
    */
    void activateVoice(double frequency, int noteNumber) {

        // Find the first available voice that isn't activated
        for(std::vector<int>::size_type i = 0; i != voices.size(); i++) {
            
            // If the voice is inactive, use it
            if (voices[i]->isInactive()) {
                voices[i]->setADSR(g_attack, g_decay, g_sustain, g_release);
                voices[i]->setFilterADSR(g_filter_attack, g_filter_decay, g_filter_sustain, g_filter_release);
                voices[i]->activate(frequency, noteNumber);
                voices[i]->setAge(0);
                return;
            }
        }
        
        // If all voices are currently being used
        int age = 0;
        int oldest = 0;
        
        // Find oldest voice
        for (std::vector<int>::size_type i = 0; i != voices.size(); i++) {
            if (voices[i]->getAge() > age) {
                age = voices[i]->getAge();
                oldest = i;
            }
        }
        
        // Deactivate it
        voices[oldest]->forceDeactivate();
        
        // Set new values
        voices[oldest]->setADSR(g_attack, g_decay, g_sustain, g_release);
        voices[oldest]->setFilterADSR(g_filter_attack, g_filter_decay, g_filter_sustain, g_filter_release);
        voices[oldest]->activate(frequency, noteNumber);
        voices[oldest]->setAge(0);
        return;

        
        /* If this point is reached, no inactive voice was found, meaning all are currently in use
         In this case, find the oldest active voice, deactivate it, and activate this voice */
        
        /* TODO: Implement voice exchange here */
        
        // Activate the new voice (recursive call)
//        activateVoice(frequency, noteNumber);

    }
    
    void releaseVoice(int noteNumber) {
        int numVoicesWithNoteNumber = 0;
        
        // Find out if more than one voice has the same note number
        for(std::vector<int>::size_type i = 0; i != voices.size(); i++) {
            if (voices[i]->getNoteNumber() == noteNumber) {
                numVoicesWithNoteNumber++;
            }
        }
        
        // If multiple voices have the same note number, find the one that isn't in the release stage
        if (numVoicesWithNoteNumber > 1) {
            for(std::vector<int>::size_type i = 0; i != voices.size(); i++) {
                if (voices[i]->isNotInReleaseStage()) {
                    // Start release on the voice not in the release stage
                    voices[i]->startRelease();
                }
            }
            
        } else {
            // Otherwise, release the voice with the specified note number
            for(std::vector<int>::size_type i = 0; i != voices.size(); i++) {
                if (voices[i]->getNoteNumber() == noteNumber) {
                    voices[i]->startRelease();
                    return;
                }
            }
        }
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
        
        // Change gain, if applicable
        if (changingGain) {
            
            // Update gain
            gain += gainChangeIncrement;
            
            // Increment the counter
            gainChangeCount++;
            
            // If the limit is reached, stop changing, reset values
            if (gainChangeCount >= GAIN_CHANGE_LENGTH) {
                gainChangeCount = 0;
                gainChangeIncrement = 0;
                changingGain = false;
            }
        }
        
        for(std::vector<int>::size_type i = 0; i != voices.size(); i++) {
            double *voiceSamples = voices[i]->getSamplesLeft(blockSize);
            for (int i=0; i<blockSize; i++) {
                samples[i] += voiceSamples[i]*gain/(double)voices.size();
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
                samples[i] += voiceSamples[i]*gain/(double)voices.size();
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
    
    void changeDetuneAmt(double newDetune) {
        for(std::vector<int>::size_type i = 0; i != voices.size(); i++) {
            voices[i]->changeDetuneAmt(newDetune);
        }
    }
    
    void changePanAmt(double newPan) {
        for(std::vector<int>::size_type i = 0; i != voices.size(); i++) {
            voices[i]->changePanAmt(newPan);
        }
    }
    
    void changePhaseMode(WavePhase wavePhase) {
        for(std::vector<int>::size_type i = 0; i != voices.size(); i++) {
            voices[i]->changePhaseMode(wavePhase);
            voices[i]->forceDeactivate();
        }
    }
    
    void setGain(double gain) {
        
        // Find out how much the gain should change by
        double change = gain - this->gain;
        
        // Determine increment that the gain will have to change with each sample in order to achieve change
        gainChangeIncrement = change/(double)GAIN_CHANGE_LENGTH;
        
        // Set count to zero
        gainChangeCount = 0;
        
        // Start changing gain
        changingGain = true;
    }
    
    void changeAttackAmt(int newAttack) { g_attack = newAttack; }
    
    void changeDecayAmt(int newDecay) { g_decay = newDecay; }
    
    void changeSustainAmt(double newSustain) { g_sustain = newSustain; }
    
    void changeReleaseAmt(int newRelease) { g_release = newRelease; }
    
    void changeFilterAttackAmt(int newAttack) { g_filter_attack = newAttack; }
    
    void changeFilterDecayAmt(int newDecay) { g_filter_decay = newDecay; }
    
    void changeFilterSustainAmt(double newSustain) { g_filter_sustain = newSustain; }
    
    void changeFilterReleaseAmt(int newRelease) { g_filter_release = newRelease; }
    
    void changeFilterCutoff(double newCutoff) {
        for(std::vector<int>::size_type i = 0; i != voices.size(); i++) {
            voices[i]->changeFilterCutoff(newCutoff);
        }
    }
    
    void changeDistortionAmt(double newDistortion) {
        for(std::vector<int>::size_type i = 0; i != voices.size(); i++) {
            voices[i]->changeDistortionAmt(newDistortion);
        }
    }
    
    double getWaveTableValueAtIndex(int i) { return voices[0]->getWaveTableValueAtIndex(i); }
    
    int getAmpEnvLength() { return g_attack + g_decay + g_release; }
    
    int getAmpEnvAttack() { return g_attack; }
    
    int getAmpEnvDecay() { return g_decay; }
    
    int getAmpEnvRelease() { return g_release; }
    
    double getAmpEnvSustain() { return g_sustain; }
    
    int getFilterEnvLength() { return g_filter_attack + g_filter_decay + g_filter_release; }
    
    int getFilterEnvAttack() { return g_filter_attack; }
    
    int getFilterEnvDecay() { return g_filter_decay; }
    
    int getFilterEnvRelease() { return g_filter_release; }
    
    double getFilterEnvSustain() { return g_filter_sustain; }
    
    // newFilterModAmt is a double between 0.0 and 1.0
    void changeFilterModAmt(double newFilterModAmt) {
        for(std::vector<int>::size_type i = 0; i != voices.size(); i++) {
            voices[i]->changeFilterModAmt(newFilterModAmt);
        }
    }
    
};

#endif /* Symphony_hpp */
