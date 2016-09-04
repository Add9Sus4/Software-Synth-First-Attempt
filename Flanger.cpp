//
//  Flanger.cpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/30/16.
//
//

#include "Flanger.hpp"

double Flanger::process(double sample) {
    double newSample = sample;
    
    // Set new length of delay based on lfo, mod amount
    int newLength = length + lfo->getNextSample()*(length*modAmount);
    
    // Make sure length is at least 2, otherwise delay will be too short at bottom of lfo range
    if (newLength < 2) newLength = 2;
    
    // Set new delay length
    delay->setLength(newLength);
    
    // Process sample with delay
    newSample = delay->process(newSample);
    
    // Return processed sample
    return newSample;
}

WaveForm *Flanger::createWaveForm(WaveType waveType, double frequency) {
    WaveForm *waveForm;
    switch (waveType) {
        case SINE:
            waveForm = new SineWaveForm(frequency);
            break;
        case SAW:
            waveForm = new SawWaveForm(frequency);
            break;
        case SQUARE:
            waveForm = new PulseWaveForm(frequency, 0.50);
            break;
        case TRIANGLE:
            waveForm = new TriangleWaveForm(frequency);
            break;
        case NOISE:
            waveForm = new NoiseWaveForm(frequency);
            break;
        default:
            break;
    }
    return waveForm;
}