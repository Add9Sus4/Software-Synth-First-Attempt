//
//  OscillatorGroup.cpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/28/16.
//
//

#include "OscillatorGroup.hpp"

// Get combined output samples from oscillators (left channel only)
double *OscillatorGroup::getSamplesLeft(int blockSize) {
    double *samples = new double[blockSize];
    for (int i=0; i<blockSize; i++) {
        samples[i] = 0.0;
    }
    
    for(std::vector<int>::size_type j = 0; j != oscillators.size(); j++) {
        double *oscSamples = oscillators[j]->getSamplesLeft(blockSize);
        for (int i=0; i<blockSize; i++) {
            samples[i] += oscSamples[i]/(double)oscillators.size();
        }
        delete oscSamples;
    }
    return samples;
}

// Get combined output samples from oscillators (right channel only)
double *OscillatorGroup::getSamplesRight(int blockSize) {
    double *samples = new double[blockSize];
    for (int i=0; i<blockSize; i++) {
        samples[i] = 0.0;
    }
    
    for(std::vector<int>::size_type j = 0; j != oscillators.size(); j++) {
        double *oscSamples = oscillators[j]->getSamplesRight(blockSize);
        for (int i=0; i<blockSize; i++) {
            samples[i] += oscSamples[i]/(double)oscillators.size();
        }
        delete oscSamples;
    }
    return samples;
}

// Sets the pulse width for the oscillators. This only has an effect if the wave type is a pulse wave.
void OscillatorGroup::setPulseWidth(double pulseWidth) {
    for(std::vector<int>::size_type i = 0; i != oscillators.size(); i++) {
        oscillators[i]->setPulseWidth(pulseWidth);
    }
}

void OscillatorGroup::setFrequency(double frequency ) {
    
    double *frequencies = new double[oscillators.size()];
    
    /* Calculate the detune amount (scaled by number of oscillators so that the min/max frequency
     remains the same. */
    double detuneAmt = 2.0/(double)oscillators.size();
    
    /* Sum of all frequencies. Needed for calculation of average frequency later, which is needed to shift
     frequencies so that their average is equal to the frequency passed into the constructor (otherwise,
     the average frequency would be too high) */
    double frequencySum = 0.0;
    
    // Calculate pan and frequency values for each oscillator in the group
    for(std::vector<int>::size_type i = 0; i != oscillators.size(); i++) {
        frequencies[i] = frequency + (double)i*detuneAmt; // frequencies offset by detune amount
        frequencySum += frequencies[i]; // Add to frequency sum
    }
    
    // Calculate average frequency of all oscillators
    double avgFrequency = frequencySum/(double)oscillators.size();
    
    // Adjust all frequencies so that their average is the correct value
    for (int i=0; i<oscillators.size(); i++) {
        frequencies[i] -= (avgFrequency - frequency); // avgFrequency will always be higher than frequency at this point
    }
    
    for(std::vector<int>::size_type i = 0; i != oscillators.size(); i++) {
        oscillators[i]->setFrequency(frequencies[i]);
    }
    
    delete frequencies;
}