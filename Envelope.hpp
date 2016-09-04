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
    
    // A class representing a point in the envelope (private inner class, since only the Envelope class need know about it)
    class EnvelopePoint {
    public:
        int x; // number of samples from beginning (0 to ENV_MAX_LENGTH)
        double y; // envelope amount (0.0 to 1.0)
        EnvelopePoint(double x, double y):x(x),y(y){}
    };
    
    // A vector containing all the points of the envelope
    std::vector<EnvelopePoint *> envelopePoints;
    
    // Current stage of the envelope
    EnvelopeStage stage;
    
    double attackIncrement, decayIncrement, releaseIncrement; // how quickly the envelope attacks, decays, and releases
    
    // The current value of the envelope at this point in time
    double currentValue;
    
public:
    
    // Create a new envelope
    Envelope();
    
    // Returns true if this envelope is inactive
    bool isInactive();
    
    /* Get the next value from the envelope. If the envelope is INACTIVE, this just returns 0s. If the envelope is in
     the ATTACK, DECAY, or RELEASE stages, it gets the next sample by taking the current one and moving along the slope
     between two points. If the envelope is in the SUSTAIN stage, it continues to return the same value repeatedly. */
    double process(double sample);
    
    // Advances the envelope to the next stage, if it is at the correct point to do so
    void goToNextStageIfApplicable();
    
    // Starts the envelope
    void start();
    
    // Enters release phase of envelope
    void release();
    
    // Stops the envelope
    void stop();
};

#endif /* Envelope_hpp */

