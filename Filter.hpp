//
//  Filter.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/28/16.
//
//

#ifndef Filter_hpp
#define Filter_hpp

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include "SampleEffect.hpp"

#define FILTER_FREQ_MIN             10
#define FILTER_FREQ_MAX             15000
#define FILTER_FREQ_DEFAULT         500

#define FILTER_CUTOFF_CHANGE_LENGTH 2000

/* filter types */
enum {
    LPF, /* low pass filter */
    HPF, /* High pass filter */
    BPF, /* band pass filter */
    NOTCH, /* Notch Filter */
    PEQ, /* Peaking band EQ filter */
    LSH, /* Low shelf filter */
    HSH /* High shelf filter */
};

class Filter : public SampleEffect {
private:
    double filter_a0, filter_a1, filter_a2, filter_a3, filter_a4;
    double filter_x1, filter_x2, filter_y1, filter_y2;
    int type;
    double dbGain;
    double freq;
    double currentOffset;
    double srate;
    double bandwidth;
    double centerFreq;
    
    double centerFreqChangeIncrement;
    int centerFreqChangeCount;
    bool changingFreq;
    
public:
    Filter(int type, double dbGain, double freq,
           double srate, double bandwidth);
    
    
    double getFreq() { return freq; }
    
    void updateCoefficients(double freqOffset);
    
    /* Computes a BiQuad filter on a sample */
    double processSample(double sample);
    
    void changeCutoff(double newCutoff) {
        if (newCutoff <= FILTER_FREQ_MAX && newCutoff >= FILTER_FREQ_MIN) {
            // Find out how much the frequency should change by
            double change = newCutoff - centerFreq;
        
            // Determine increment that the gain will have to change with each sample in order to achieve change
            centerFreqChangeIncrement = change/(double)FILTER_CUTOFF_CHANGE_LENGTH;
        
            // Set count to zero
            centerFreqChangeCount = 0;
        
            // Start changing gain
            changingFreq = true;
        }
    }

};

#endif /* Filter_hpp */
