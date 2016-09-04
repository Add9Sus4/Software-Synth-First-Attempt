//
//  Voice.cpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/1/16.
//
//

#include "Voice.hpp"

// Create new voice
Voice::Voice() {
    
    // Initially, voice is not in use
    noteNumber = VOICE_NOT_IN_USE;
    
    // TODO: Implement voice creation.
    
    // Create oscillator group. For now, just assume some default argments
    oscillatorGroup = new OscillatorGroup(16, Bb_2, WaveType::SAW);
    
    // Create envelope.
    ampEnvelopeLeft = new Envelope();
    ampEnvelopeRight = new Envelope();
}

// Returns true if the voice is not in use
bool Voice::isInactive() {
    return (noteNumber == VOICE_NOT_IN_USE) ? true : false;
}

bool Voice::envIsInactive() {
    if (ampEnvelopeLeft->isInactive() && ampEnvelopeRight->isInactive()) {
        return true;
    }
    return false;
}

void Voice::activate(double frequency, int noteNumber) {
    
    // Assign noteNumber to voice
    this->noteNumber = noteNumber;
    
    // TODO: Implement voice activation
    oscillatorGroup->setFrequency(frequency);
    
    ampEnvelopeLeft->start();
    ampEnvelopeRight->start();
}

void Voice::forceDeactivate() {
    noteNumber = VOICE_NOT_IN_USE;
    ampEnvelopeRight->stop();
    ampEnvelopeLeft->stop();
}

void Voice::deactivate() {
    
    // Set noteNumber to not in use
//    noteNumber = VOICE_NOT_IN_USE;
    
    // TODO: Implement voice deactivation
    ampEnvelopeLeft->release();
    ampEnvelopeRight->release();
}

// Get combined output samples from oscillator group (left channel only)
double *Voice::getSamplesLeft(int blockSize) {
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

// Get combined output samples from oscillator group (right channel only)
double *Voice::getSamplesRight(int blockSize) {
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