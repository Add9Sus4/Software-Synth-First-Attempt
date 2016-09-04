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
#include "SampleEffect.hpp"

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
    double srate;
    double bandwidth;
    double centerFreq;
    
public:
    Filter(int type, double dbGain, double freq,
           double srate, double bandwidth);
    
    
    double getFreq() { return freq; }
    
    void updateCoefficients(double freq);
    
    /* Computes a BiQuad filter on a sample */
    double process(double sample);

};

#endif /* Filter_hpp */
