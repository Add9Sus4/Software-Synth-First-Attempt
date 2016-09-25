//
//  Envelope.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/23/16.
//
//

#ifndef Envelope_hpp
#define Envelope_hpp

#include <math.h>
#include <stdio.h>

#include "Modulator.hpp"
#include "Phasor.hpp"

typedef enum Stage {
    ATTACK,
    DECAY,
    SUSTAIN,
    RELEASE,
    INACTIVE
} Stage;

class Envelope : public Modulator {
public:
    Envelope() {
        sustain = 0.5;
        int attack_duration = SAMPLE_RATE;
        int decay_duration = SAMPLE_RATE;
        int release_duration = SAMPLE_RATE;
        
        initial = new EnvelopePoint(0, 0.0);
        attack = new EnvelopePoint(attack_duration, 1.0);
        decay = new EnvelopePoint(attack_duration + decay_duration, sustain);
        release = new EnvelopePoint(attack_duration + decay_duration + release_duration, 0.0);
        
        samplesElapsed = 0;
        
        stage = Stage::INACTIVE;
    }
    
    double modulate(double value) {
        return value*getCurrentValue();
    }
    
    // Start the envelope
    void trigger(int attack_duration, int decay_duration, double sustain, int release_duration) {
        setSustain(sustain);
        attack->setX(attack_duration);
        decay->setX(attack_duration + decay_duration);
        decay->setY(sustain);
        release->setX(attack_duration + decay_duration + release_duration);
        stage = Stage::ATTACK;
    }
    
    // Returns the current value of the envelope
    double getCurrentValue() {
        double currentValue = 1.0;
        // Which stage are we in?
        int length = getLength(stage);
        double heightChange = getHeightChange(stage);
        double progressThroughStage = (double)(samplesElapsed - getBeginningX(stage))/(double)length;
        if (stage == Stage::SUSTAIN) {
            currentValue = sustain;
        } else if (stage == Stage::INACTIVE) {
            currentValue = 0.0;
            samplesElapsed = 0;
        } else {
            currentValue = heightChange*pow(progressThroughStage, 1.0) + getBeginningY(stage);
            samplesElapsed++;
        }
        
        // Make sure we are in the right stage
        if (stage == ATTACK && samplesElapsed >= getBeginningX(DECAY)) {
            stage = DECAY;
        }
        if (stage == DECAY && samplesElapsed >= getBeginningX(RELEASE)) {
            stage = SUSTAIN;
        }
        if (stage == RELEASE && samplesElapsed >= attack->getX() + decay->getX() + release->getX()) {
            stage = INACTIVE;
        }
        
        return currentValue;
    }
    
    void setSustain(double sustain) { this->sustain = sustain; }

private:
    
    class EnvelopePoint {
    public:
        EnvelopePoint(int x, double y) {
            this->x = x;
            this->y = y;
        }
        void setX(int x) { this->x = x; }
        void setY(double y) { this->y = y; }
        int getX() { return x; }
        double getY() { return y; }
    private:
        int x;
        double y;
    };
    
    // Get the beginning x value of a particular stage
    int getBeginningX(Stage stage) {
        int beginning = 0;
        switch (stage) {
            case ATTACK:
                beginning = initial->getX();
                break;
            case DECAY:
                beginning = attack->getX();
                break;
            case SUSTAIN:
                beginning = decay->getX();
                break;
            case RELEASE:
                beginning = decay->getX();
                break;
            case INACTIVE:
                beginning = 0;
                break;
            default:
                beginning = 0;
                break;
        }
        return beginning;
    }
    
    // Get the beginning y value of a particular stage
    double getBeginningY(Stage stage) {
        double beginning = 0.0;
        switch (stage) {
            case ATTACK:
                beginning = initial->getY();
                break;
            case DECAY:
                beginning = attack->getY();
                break;
            case SUSTAIN:
                beginning = decay->getY();
                break;
            case RELEASE:
                beginning = decay->getY();
                break;
            case INACTIVE:
                beginning = 0.0;
                break;
            default:
                beginning = 0.0;
                break;
        }
        return beginning;
    }
    
    // Calculate length, in samples, between two envelope points
    int getLength(EnvelopePoint* start, EnvelopePoint* end) {
        return end->getX() - start->getX();
    }
    
    // Calculate height change, in samples, between two envelope points
    double getHeightChange(EnvelopePoint* start, EnvelopePoint* end) {
        return end->getY() - start->getY();
    }
    
    // Calculate length, in samples, of a given envelope stage
    int getLength(Stage stage) {
        int stageLength = 0;
        switch (stage) {
            case ATTACK:
                stageLength = getLength(initial, attack);
                break;
            case DECAY:
                stageLength = getLength(attack, decay);
                break;
            case SUSTAIN:
                stageLength = 0;
                break;
            case RELEASE:
                stageLength = getLength(decay, release);
                break;
            case INACTIVE:
                stageLength = 0;
                break;
            default:
                stageLength = 0;
                break;
        }
        return stageLength;
    }
    
    // Calculate height change of a given envelope stage
    double getHeightChange(Stage stage) {
        double heightChange = 0.0;
        switch (stage) {
            case ATTACK:
                heightChange = getHeightChange(initial, attack);
                break;
            case DECAY:
                heightChange = getHeightChange(attack, decay);
                break;
            case SUSTAIN:
                heightChange = 0.0;
                break;
            case RELEASE:
                heightChange = getHeightChange(decay, release);
                break;
            case INACTIVE:
                heightChange = 0.0;
                break;
            default:
                heightChange = 0.0;
                break;
        }
        return heightChange;
    }
    
    double sustain;
    
    int samplesElapsed;
    
    Stage stage;
    
    EnvelopePoint* initial;
    EnvelopePoint* attack;
    EnvelopePoint* decay;
    EnvelopePoint* release;
};

#endif /* Envelope_hpp */
