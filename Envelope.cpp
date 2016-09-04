//
//  Envelope.cpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/2/16.
//
//

#include "Envelope.hpp"

// Create a new envelope
Envelope::Envelope() {
  
    // Create 4 initial points (initial, attack, decay, release) with default values
    EnvelopePoint *initial = new EnvelopePoint(0, 0.0); // Start at this point on note on message
    EnvelopePoint *attack = new EnvelopePoint(661, 1.0); // Go to this point
    EnvelopePoint *decay = new EnvelopePoint(10661, 0.2); // Then go to this point and wait (second argument here is sustain)
    EnvelopePoint *release = new EnvelopePoint(20761, 0.0); // When note off message is received, go to this point
    
    // Calculate slopes (used to get next envelope value, depending on envelope stage)
    attackIncrement = (attack->y - initial->y)/(double)(attack->x - initial->x);
    decayIncrement = (decay->y - attack->y)/(double)(decay->x - attack->x);
    releaseIncrement = (release->y - decay->y)/(double)(release->x - decay->x);
    
//    printf("attackIncrement: %f, decayIncrement: %f, releaseIncrement: %f\n", attackIncrement, decayIncrement, releaseIncrement);
    
    // Add points to vector
    envelopePoints.push_back(initial);
    envelopePoints.push_back(attack);
    envelopePoints.push_back(decay);
    envelopePoints.push_back(release);
    
    // Set initial stage to INACTIVE
    stage = EnvelopeStage::INACTIVE;
    
    // Set current value of the envelope to 0
    currentValue = 0.0;
}

/* Get the next value from the envelope. If the envelope is INACTIVE, this just returns 0s. If the envelope is in
 the ATTACK, DECAY, or RELEASE stages, it gets the next sample by taking the current one and moving along the slope
 between two points. If the envelope is in the SUSTAIN stage, it continues to return the same value repeatedly. */
double Envelope::process(double sample) {
    double newSample = 0.0;
    switch (stage) {
        case EnvelopeStage::INACTIVE:
            // newSample is already 0.0, which is what we want for inactive state
            break;
        case EnvelopeStage::ATTACK:
            newSample = currentValue += attackIncrement;
            break;
        case EnvelopeStage::DECAY:
            newSample = currentValue += decayIncrement;
            break;
        case EnvelopeStage::SUSTAIN:
            newSample = currentValue;
            break;
        case EnvelopeStage::RELEASE:
            newSample = currentValue += releaseIncrement;
            break;
        default:
            break;
    }
    goToNextStageIfApplicable();
//    std::cout << "Sample: " << sample << std::endl;
//    std::cout << "Envelope stage: " << stage << ", envelope value: " << currentValue << std::endl;
    return sample * currentValue;
}

// Advances the envelope to the next stage, if it is the correct time to do so
void Envelope::goToNextStageIfApplicable() {
    switch (stage) {
        case EnvelopeStage::INACTIVE:
            
            return; // Inactive can only be interrupted by a note on message
            break;
            
        case EnvelopeStage::ATTACK:
            
            // If attack is over, start decay
            if (currentValue >= envelopePoints[1]->y) {
                currentValue = envelopePoints[1]->y;
                stage = EnvelopeStage::DECAY;
                return;
            }
            break;
            
        case EnvelopeStage::DECAY:
            
            // If decay is over, start sustain
            if (currentValue <= envelopePoints[2]->y) {
                currentValue = envelopePoints[2]->y;
                stage = EnvelopeStage::SUSTAIN;
                return;
            }
            break;
            
        case EnvelopeStage::SUSTAIN:
            return; // Sustain can only be interrupted by a note off message
            break;
            
        case EnvelopeStage::RELEASE:
            
            // If release is over, set to inactive
            if (currentValue <= envelopePoints[3]->y) {
                currentValue = 0.0;
                stage = EnvelopeStage::INACTIVE;
                return;
            }
            break;
            
        default:
            break;
    }
}

bool Envelope::isInactive() {
    return stage == EnvelopeStage::INACTIVE;
}

void Envelope::start() {
    stage = EnvelopeStage::ATTACK;
}

void Envelope::release() {
    stage = EnvelopeStage::RELEASE;
}

void Envelope::stop() {
    stage = EnvelopeStage::INACTIVE;
}