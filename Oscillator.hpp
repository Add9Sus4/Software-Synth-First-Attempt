//
//  Oscillator.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/28/16.
//
//  This class represents a generic oscillator. In this sense, an oscillator is simply a
//  repeating pattern.
//
//--------------------------------------------------------------------------------------------------------------//


#ifndef Oscillator_hpp
#define Oscillator_hpp

#include <stdio.h>
#include <iostream>
#include "WaveForm.hpp"
#include "SineWaveForm.hpp"
#include "SawWaveForm.hpp"
#include "TriangleWaveForm.hpp"
#include "NoiseWaveForm.hpp"
#include "PulseWaveForm.hpp"

typedef enum WaveType {
    SINE,
    SAW,
    SQUARE,
    TRIANGLE,
    NOISE,
    PULSE
} WaveType;

class Oscillator {
protected:
    
    WaveForm *waveFormLeft;
    WaveForm *waveFormRight;
    WaveType waveType;
    double pulseWidth;
    
    // The number of times that the oscillator repeats each second
    double frequency;
    
    // Scaling factor for audio produced by this oscillator. Value must be between 0.0f and 1.0f.
    double amplitude;
    
    // -1.0 (hard left) to 1.0 (hard right)
    double pan;
    
    double phase;
    
public:
    
    Oscillator(double frequency, double pan, WaveType waveType) {
        this->waveType = waveType;
        
        pulseWidth = 0.5;
        
        // Sync mode
        double phase = 0.0;
        
        // Free mode
        phase = ((double)(rand() % 1000)/999.0);
        this->phase = phase;
        
        switch (waveType) {
            case SINE:
                waveFormLeft = new SineWaveForm(frequency, phase);
                waveFormRight = new SineWaveForm(frequency, phase);
                break;
            case SAW:
                waveFormLeft = new SawWaveForm(frequency, phase);
                waveFormRight = new SawWaveForm(frequency, phase);
                break;
            case SQUARE:
                waveFormLeft = new PulseWaveForm(frequency, 0.5);
                waveFormRight = new PulseWaveForm(frequency, 0.5);
                break;
            case TRIANGLE:
                waveFormLeft = new TriangleWaveForm(frequency, phase);
                waveFormRight = new TriangleWaveForm(frequency, phase);
                break;
            case NOISE:
                waveFormLeft = new NoiseWaveForm(frequency, phase);
                waveFormRight = new NoiseWaveForm(frequency, phase);
                break;
            case PULSE:
                waveFormLeft = new PulseWaveForm(frequency, phase);
                waveFormRight = new PulseWaveForm(frequency, phase);
                break;
            default:
                break;
        }
        
        
        this->pan = pan;
        this->frequency = frequency;
    };
    
    Oscillator(double frequency, double pan, WaveType waveType, double initialPhase) {
        this->waveType = waveType;
        pulseWidth = 0.5;
        
        switch (waveType) {
            case SINE:
                waveFormLeft = new SineWaveForm(frequency, initialPhase);
                waveFormRight = new SineWaveForm(frequency, initialPhase);
                break;
            case SAW:
                waveFormLeft = new SawWaveForm(frequency, initialPhase);
                waveFormRight = new SawWaveForm(frequency, initialPhase);
                break;
            case SQUARE:
                waveFormLeft = new PulseWaveForm(frequency, 0.5);
                waveFormRight = new PulseWaveForm(frequency, 0.5);
                break;
            case TRIANGLE:
                waveFormLeft = new TriangleWaveForm(frequency, initialPhase);
                waveFormRight = new TriangleWaveForm(frequency, initialPhase);
                break;
            case NOISE:
                waveFormLeft = new NoiseWaveForm(frequency, initialPhase);
                waveFormRight = new NoiseWaveForm(frequency, initialPhase);
                break;
            case PULSE:
                waveFormLeft = new PulseWaveForm(frequency, pulseWidth);
                waveFormRight = new PulseWaveForm(frequency, pulseWidth);
                break;
            default:
                break;
        }
        
        
        this->pan = pan;
        this->frequency = frequency;
    };
    
    void changeWaveType(WaveType waveType) {
        this->waveType = waveType;
        
        pulseWidth = 0.5;
        
        WaveForm *tempLeft = waveFormLeft;
        WaveForm *tempRight = waveFormRight;
        
        switch (waveType) {
            case SINE:
                waveFormLeft = new SineWaveForm(frequency, phase);
                waveFormRight = new SineWaveForm(frequency, phase);
                break;
            case SAW:
                waveFormLeft = new SawWaveForm(frequency, phase);
                waveFormRight = new SawWaveForm(frequency, phase);
                break;
            case SQUARE:
                waveFormLeft = new PulseWaveForm(frequency, 0.5);
                waveFormRight = new PulseWaveForm(frequency, 0.5);
                break;
            case TRIANGLE:
                waveFormLeft = new TriangleWaveForm(frequency, phase);
                waveFormRight = new TriangleWaveForm(frequency, phase);
                break;
            case NOISE:
                waveFormLeft = new NoiseWaveForm(frequency, phase);
                waveFormRight = new NoiseWaveForm(frequency, phase);
                break;
            case PULSE:
                waveFormLeft = new PulseWaveForm(frequency, phase);
                waveFormRight = new PulseWaveForm(frequency, phase);
                break;
            default:
                break;
        }
        delete tempLeft;
        delete tempRight;
        
    }
    
    void invertPhase() { waveFormLeft->invertPhase(); waveFormRight->invertPhase(); }
    
    void restorePhase() { waveFormLeft->restorePhase(); waveFormRight->restorePhase(); }
    
    // Returns the frequency of this oscillator
    double getFrequency() { return frequency; }
    
    // Returns the amplitude of this oscillator
    double getAmplitude() { return amplitude; }
    
    // Returns samples generated by the oscillator for the next audio block
    double *getSamplesLeft(int blockSize);
    double *getSamplesRight(int blockSize);
    
    void setPulseWidth(double pulseWidth);
    
    // Sets the frequency of the oscillator
    void setFrequency(double frequency);
    
    void setPan(double pan) {
        this->pan = pan;
    }
    
};



#endif /* Oscillator_hpp */
