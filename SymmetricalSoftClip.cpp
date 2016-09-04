//
//  SymmetricalSoftClip.cpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/31/16.
//
//

#include "SymmetricalSoftClip.hpp"

double SymmetricalSoftClip::process(double sample) {
    double newSample = 1.0;
    if (fabs(sample) > 0.666666) {
        newSample = 1.0;
    } else if (fabs(sample) > 0.333333) {
        newSample = (3.0 - pow((2.0-3.0*sample), 2))/3.0;
    } else {
        newSample = 2*sample;
    }
    return newSample;
}