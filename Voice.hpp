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
    
    int attack;
    int decay;
    double sustain;
    int release;
    
public:
    
    // Creates a new voice
    Voice(int attack, int decay, double sustain, int release) {
        this->attack = attack;
        this->decay = decay;
        this->sustain = sustain;
        this->release = release;
        // Initially, voice is not in use
        noteNumber = VOICE_NOT_IN_USE;
        
        // TODO: Implement voice creation.
        
        // Create oscillator group. For now, just assume some default argments
        oscillatorGroup = new OscillatorGroup(16, Bb_2, WaveType::SAW);
        
        // Create envelope.
        ampEnvelopeLeft = new Envelope(attack, decay, sustain, release);
        ampEnvelopeRight = new Envelope(attack, decay, sustain, release);
    }
    
    // Returns the noteNumber of this voice
    int getNoteNumber() { return noteNumber; }
    
    // Returns true if the voice is currently not in use
    bool isInactive() {
         return (noteNumber == VOICE_NOT_IN_USE) ? true : false;
    }
    
    // Activates a voice by assigning it an note number and starting all relevant processing (oscillators, lfos, envelopes, etc)
    void activate(double frequency, int noteNumber) {
        
        // Assign noteNumber to voice
        this->noteNumber = noteNumber;
        
        // TODO: Implement voice activation
        oscillatorGroup->setFrequency(frequency);
        ampEnvelopeLeft->setADSR(attack, decay, sustain, release);
        ampEnvelopeRight->setADSR(attack, decay, sustain, release);
        ampEnvelopeLeft->start();
        ampEnvelopeRight->start();
    }
    
    // Deactivates a voice by assigning its noteNumber to VOICE_NOT_IN_USE and stopping all relevant processing (oscillators, lfos, envelopes, etc)
    void deactivate() {
        // Set noteNumber to not in use
        //    noteNumber = VOICE_NOT_IN_USE;
        
        // TODO: Implement voice deactivation
        ampEnvelopeLeft->release();
        ampEnvelopeRight->release();
    }
    
    void forceDeactivate() {
        noteNumber = VOICE_NOT_IN_USE;
        ampEnvelopeRight->stop();
        ampEnvelopeLeft->stop();
    }
    
    // Returns true if all envelopes are inactive
    bool envIsInactive() {
        if (ampEnvelopeLeft->isInactive() && ampEnvelopeRight->isInactive()) {
            return true;
        }
        return false;
    }
    
    // Get combined output samples from oscillator group
    double *getSamplesLeft(int blockSize) {
        double *samples = new double[blockSize];
        for (int i=0; i<blockSize; i++) {
            samples[i] = 0.0;
        }
        
        // Only get samples if the voice is active (otherwise, just send 0s)
        if (!envIsInactive()) {
            double *oscGroupSamples = oscillatorGroup->getSamplesLeft(blockSize);
            for (int i=0; i<blockSize; i++) {
                samples[i] += ampEnvelopeLeft->process(oscGroupSamples[i]);
            }
            delete oscGroupSamples;
        } else {
            noteNumber = VOICE_NOT_IN_USE;
        }
        
        return samples;
    }
    double *getSamplesRight(int blockSize) {
        double *samples = new double[blockSize];
        for (int i=0; i<blockSize; i++) {
            samples[i] = 0.0;
        }
        
        // Only get samples if the voice is active (otherwise, just send 0s)
        if (!envIsInactive()) {
            double *oscGroupSamples = oscillatorGroup->getSamplesRight(blockSize);
            for (int i=0; i<blockSize; i++) {
                samples[i] += ampEnvelopeRight->process(oscGroupSamples[i]);
            }
            delete oscGroupSamples;
        } else {
            noteNumber = VOICE_NOT_IN_USE;
        }
        
        return samples;
    }
    
    void changeWaveType(WaveType waveType) {
        oscillatorGroup->changeWaveType(waveType);
    }
    
    WaveType getWaveType() { return oscillatorGroup->getWaveType(); }
    
    void changeDetuneAmt(double newDetune) {
        oscillatorGroup->changeDetuneAmt(newDetune);
    }
    
    void changePanAmt(double newPan) {
        oscillatorGroup->changePanAmt(newPan);
    }
    
    void changePhaseMode(WavePhase wavePhase) {
        oscillatorGroup->changePhaseMode(wavePhase);
    }
    
    void setADSR(int attack, int decay, double sustain, int release) {
        this->attack = attack;
        this->decay = decay;
        this->sustain = sustain;
        this->release = release;
    }
};

#endif /* Voice_hpp */
