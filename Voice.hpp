//
//  Voice.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/1/16.
//
//  In a polyphonic synthesizer, each individual note is represented by a Voice.

#ifndef Voice_hpp
#define Voice_hpp

#define VOICE_NOT_IN_USE                -1
#define MAX_FILTER_MOD_AMT              22000
#define FILTER_MOD_AMT_CHANGE_LENGTH    20

#include <stdio.h>
#include <stdbool.h>
#include "OscillatorGroup.hpp"
#include "Envelope.hpp"
#include "Distortion.hpp"

class Voice {
private:
    
    // The group of oscillators associated with this voice
    OscillatorGroup *oscillatorGroup;
    
    Filter *filterLeft;
    Filter *filterRight;
    
    // From 0.0 to 1.0
    double filterModAmt;
    
    double filterModAmtChangeIncrement;
    int filterModAmtChangeCount;
    bool changingfilterModAmt;
    
    // The note number associated with this voice
    int noteNumber;
    
    // Amp envelope
    Envelope *ampEnvelopeLeft;
    Envelope *ampEnvelopeRight;
    
    // Filter envelope
    Envelope *filterEnvelopeLeft;
    Envelope *filterEnvelopeRight;
    
    // Distortion
    Distortion *distortionLeft;
    Distortion *distortionRight;
    
    // Envelope ADSR
    int attack, filterAttack;
    int decay, filterDecay;
    double sustain, filterSustain;
    int release, filterRelease;
    
    bool active;
    
    int age;
    
public:
    
    // Creates a new voice
    Voice(int attack, int decay, double sustain, int release, int filterAttack, int filterDecay, double filterSustain, int filterRelease) {
        
        filterModAmt = 0.0;
        
        filterModAmtChangeIncrement = 0.0;
        filterModAmtChangeCount = 0;
        changingfilterModAmt = false;
        
        this->attack = attack;
        this->decay = decay;
        this->sustain = sustain;
        this->release = release;
        this->filterAttack = filterAttack;
        this->filterDecay = filterDecay;
        this->filterSustain = filterSustain;
        this->filterRelease = filterRelease;
        active = false;
        
        age = 0;
        // Initially, voice is not in use
        noteNumber = VOICE_NOT_IN_USE;
        
        // TODO: Implement voice creation.
        
        // Create oscillator group. For now, just assume some default argments
        oscillatorGroup = new OscillatorGroup(6, Bb_2, WaveType::SAW);
        
        // Create filter
        filterLeft = new Filter(LPF, 0.0, FILTER_FREQ_DEFAULT, SAMPLE_RATE, 1);
        filterRight = new Filter(LPF, 0.0, FILTER_FREQ_DEFAULT, SAMPLE_RATE, 1);
        
        // Create distortion
        distortionLeft = new Distortion(1.0);
        distortionRight = new Distortion(1.0);
        
        // Create envelope.
        ampEnvelopeLeft = new Envelope(attack, decay, sustain, release);
        ampEnvelopeRight = new Envelope(attack, decay, sustain, release);
        
        // Create filter envelope
        filterEnvelopeLeft = new Envelope(filterAttack, filterDecay, filterSustain, filterRelease);
        filterEnvelopeRight = new Envelope(filterAttack, filterDecay, filterSustain, filterRelease);
    }
    
    // Returns the noteNumber of this voice
    int getNoteNumber() { return noteNumber; }
    
    // Returns true if the voice is currently not in use
    bool isInactive() {
         return !active;
    }
    
    bool isActive() {
        return active;
    }
    
    void setAge(int age) {
        this->age = age;
    }
    
    int getAge() { return age; }
    
    // Activates a voice by assigning it an note number and starting all relevant processing (oscillators, lfos, envelopes, etc)
    void activate(double frequency, int noteNumber) {
        age = 0;
        active = true;
        
        // Assign noteNumber to voice
        this->noteNumber = noteNumber;
        
        // TODO: Implement voice activation
        oscillatorGroup->setFrequency(frequency);
        ampEnvelopeLeft->setADSR(attack, decay, sustain, release);
        ampEnvelopeRight->setADSR(attack, decay, sustain, release);
        filterEnvelopeLeft->setADSR(filterAttack, filterDecay, filterSustain, filterRelease);
        filterEnvelopeRight->setADSR(filterAttack, filterDecay, filterSustain, filterRelease);
        ampEnvelopeLeft->start();
        ampEnvelopeRight->start();
        filterEnvelopeLeft->start();
        filterEnvelopeRight->start();
    }
    
    void startRelease() {
        ampEnvelopeLeft->release();
        ampEnvelopeRight->release();
        filterEnvelopeLeft->release();
        filterEnvelopeRight->release();
    }
    
    void forceDeactivate() {
        if (active) {
            noteNumber = VOICE_NOT_IN_USE;
            ampEnvelopeRight->stop();
            ampEnvelopeLeft->stop();
            filterEnvelopeRight->stop();
            filterEnvelopeLeft->stop();
            active = false;
        }
    }
    
    bool isNotInReleaseStage() {
        if (ampEnvelopeLeft->getStage() == EnvelopeStage::ATTACK ||
            ampEnvelopeLeft->getStage() == EnvelopeStage::DECAY ||
            ampEnvelopeLeft->getStage() == EnvelopeStage::SUSTAIN ||
            filterEnvelopeLeft->getStage() == EnvelopeStage::ATTACK ||
            filterEnvelopeLeft->getStage() == EnvelopeStage::DECAY ||
            filterEnvelopeLeft->getStage() == EnvelopeStage::SUSTAIN) {
            return true;
        } else {
            return false;
        }
    }
    
    bool isInReleaseStage() {
        if (ampEnvelopeLeft->getStage() == EnvelopeStage::RELEASE &&
            filterEnvelopeLeft->getStage() == EnvelopeStage::RELEASE) {
            return true;
        } else {
            return false;
        }
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
        
        // Change filter mod amt, if applicable
        if (changingfilterModAmt) {
            
            // Update filter mod amt
            filterModAmt += filterModAmtChangeIncrement;
            
            // Increment the counter
            filterModAmtChangeCount++;
            
            // If the limit is reached, stop changing, reset values
            if (filterModAmtChangeCount >= FILTER_MOD_AMT_CHANGE_LENGTH) {
                filterModAmtChangeCount = 0;
                filterModAmtChangeIncrement = 0.0;
                changingfilterModAmt = false;
            }
        }
        
        // Only get samples if the voice is active (otherwise, just send 0s)
        if (!envIsInactive()) {
            
//            double *oscGroupSamples = oscillatorGroup->getSamplesLeft(blockSize);
//            for (int i=0; i<blockSize; i++) {
//                samples[i] = ampEnvelopeLeft->process(filterLeft->process(distortionLeft->process(oscGroupSamples[i])));
//                filterLeft->updateCoefficients(filterEnvelopeLeft->process(filterModAmt*(double)MAX_FILTER_MOD_AMT));
//                age++;
//            }
//            delete oscGroupSamples;
        } else {
            if (active) {
                forceDeactivate();
            }
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
            
//            double *oscGroupSamples = oscillatorGroup->getSamplesRight(blockSize);
//            for (int i=0; i<blockSize; i++) {
//                samples[i] = ampEnvelopeRight->process(filterRight->process(distortionRight->process(oscGroupSamples[i])));
//                filterRight->updateCoefficients(filterEnvelopeRight->process(filterModAmt*(double)MAX_FILTER_MOD_AMT));
//            }
//            delete oscGroupSamples;
        } else {
            if (active) {
                forceDeactivate();
            }
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
    
    void setFilterADSR(int attack, int decay, double sustain, int release) {
        this->filterAttack = attack;
        this->filterDecay = decay;
        this->filterSustain = sustain;
        this->filterRelease = release;
    }
    
    void changeFilterCutoff(double newCutoff) {
        filterLeft->changeCutoff(newCutoff);
        filterRight->changeCutoff(newCutoff);
    }
    
    double getWaveTableValueAtIndex(int i) {
        return oscillatorGroup->getWaveTableValueAtIndex(i);
    }
    
    void changeDistortionAmt(double newDistortion) {
        distortionLeft->changeDistortionAmt(newDistortion);
        distortionRight->changeDistortionAmt(newDistortion);
    }
    
    // newFilterModAmt is a double between 0.0 and 1.0
    void changeFilterModAmt(double newFilterModAmt) {
        
        // Find out how much the mod amount should change by
        double change = newFilterModAmt - filterModAmt;
        
        // Determine increment that the gain will have to change with each sample in order to achieve change
        filterModAmtChangeIncrement = change/(double)FILTER_MOD_AMT_CHANGE_LENGTH;
        
        // Set count to zero
        filterModAmtChangeCount = 0;
        
        // Start changing gain
        changingfilterModAmt = true;
    }
    
    
};

#endif /* Voice_hpp */
