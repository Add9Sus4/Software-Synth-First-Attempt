//
//  SymmetricalSoftClip.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/31/16.
//
//

#ifndef SymmetricalSoftClip_hpp
#define SymmetricalSoftClip_hpp

#include <stdio.h>
#include <math.h>
#include "SampleEffect.hpp"

class SymmetricalSoftClip : public SampleEffect {
    
public:
    double process(double sample) {
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
};

#endif /* SymmetricalSoftClip_hpp */
