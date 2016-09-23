//
//  Envelope.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/2/16.
//
//

#ifndef Envelope_hpp
#define Envelope_hpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#define ATTACK_MIN  10
#define ATTACK_DEFAULT  661
#define ATTACK_MAX  44100*5
#define DECAY_MIN   10
#define DECAY_DEFAULT   10000
#define DECAY_MAX   44100*5
#define SUSTAIN_MIN 0.0
#define SUSTAIN_DEFAULT 0.2
#define SUSTAIN_MAX 1.0
#define RELEASE_MIN 10
#define RELEASE_DEFAULT 10100
#define RELEASE_MAX 44100*5

enum EnvelopeStage {
    INACTIVE,
    ATTACK,
    DECAY,
    SUSTAIN,
    RELEASE
};

// The envelope class itself
class Envelope {
private:
    
    int attack;
    int decay;
    double sustain;
    int rel;
    
    // Current stage of the envelope
    EnvelopeStage stage;
    
    double attackIncrement, decayIncrement, releaseIncrement; // how quickly the envelope attacks, decays, and releases
    
    // The current value of the envelope at this point in time
    double currentValue;
    
    int sampleIndex;
    
public:
    
    // Create a new envelope
    Envelope(int attack, int decay, double sustain, int rel) {
        
        currentValue = 0.0;
        sampleIndex = 0;
        
        this->attack = attack;
        this->decay = decay;
        this->sustain = sustain;
        this->rel = rel;
        
        attackIncrement = 1.0/(double)attack;
        decayIncrement = -(1.0 - sustain)/(double)decay;
        releaseIncrement = -sustain/(double)rel;
        
        // Set initial stage to INACTIVE
        stage = EnvelopeStage::INACTIVE;
    }
    
    // Returns true if this envelope is inactive
    bool isInactive() {
        return stage == EnvelopeStage::INACTIVE;

    }
    
    /* Get the next value from the envelope. If the envelope is INACTIVE, this just returns 0s. If the envelope is in
     the ATTACK, DECAY, or RELEASE stages, it gets the next sample by taking the current one and moving along the slope
     between two points. If the envelope is in the SUSTAIN stage, it continues to return the same value repeatedly. */
    double process(double sample) {
        double newSample = 0.0;
        switch (stage) {
            case EnvelopeStage::INACTIVE:
                // newSample is already 0.0, which is what we want for inactive state
                break;
            case EnvelopeStage::ATTACK:
                newSample = currentValue += attackIncrement;
                sampleIndex++;
                break;
            case EnvelopeStage::DECAY:
                newSample = currentValue += decayIncrement;
                sampleIndex++;
                break;
            case EnvelopeStage::SUSTAIN:
                newSample = currentValue;
                break;
            case EnvelopeStage::RELEASE:
                newSample = currentValue += releaseIncrement;
                sampleIndex++;
                break;
            default:
                break;
        }
        goToNextStageIfApplicable();
        return sample * currentValue;
    }
    
    // Advances the envelope to the next stage, if it is at the correct point to do so
    void goToNextStageIfApplicable() {
        switch (stage) {
            case EnvelopeStage::INACTIVE:
                
                return; // Inactive can only be interrupted by a note on message
                break;
                
            case EnvelopeStage::ATTACK:
                
                // If attack is over, start decay
                if (sampleIndex >= attack) {
                    currentValue = 1.0;
                    stage = EnvelopeStage::DECAY;
                    return;
                }
                break;
                
            case EnvelopeStage::DECAY:
                
                // If decay is over, start sustain
                if (sampleIndex >= attack + decay) {
                    currentValue = sustain;
                    stage = EnvelopeStage::SUSTAIN;
                    return;
                }
                break;
                
            case EnvelopeStage::SUSTAIN:
                return; // Sustain can only be interrupted by a note off message
                break;
                
            case EnvelopeStage::RELEASE:
                
                // If release is over, set to inactive
                if (sampleIndex >= attack + decay + rel) {
                    currentValue = 0.0;
                    sampleIndex = 0;
                    stage = EnvelopeStage::INACTIVE;
                    return;
                }
                break;
                
            default:
                break;
        }

    }
    
    void setADSR(int attack, int decay, double sustain, int rel) {
        this->attack = attack;
        this->decay = decay;
        this->sustain = sustain;
        this->rel = rel;
        
        attackIncrement = 1.0/(double)attack;
        decayIncrement = -(1.0 - sustain)/(double)decay;
        releaseIncrement = -sustain/(double)rel;
    }
    
    // Starts the envelope
    void start() {
        currentValue = 0.0;
        sampleIndex = 0;
        stage = EnvelopeStage::ATTACK;

    }
    
    // Enters release phase of envelope
    void release() {
        sampleIndex = attack + decay;
        releaseIncrement = -currentValue/(double)rel;
        stage = EnvelopeStage::RELEASE;
    }
    
    // Stops the envelope
    void stop() {
        stage = EnvelopeStage::INACTIVE;
        currentValue = 0.0;
        sampleIndex = 0;
    }
    
    EnvelopeStage getStage() { return stage; }
};

#endif /* Envelope_hpp */

