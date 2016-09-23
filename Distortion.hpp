//
//  Distortion.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/31/16.
//
//

#ifndef Distortion_hpp
#define Distortion_hpp

#include <stdio.h>
#include <math.h>
#include "SampleEffect.hpp"

class Distortion : public SampleEffect {
private:
    double alpha;
public:
    Distortion(double alpha) {
        this->alpha = alpha;
    }
    double process(double sample) {
        double output = (sample /fabs(sample))*(1 - exp(alpha*pow(sample, 2)/fabs(sample)))/(alpha/10.0);
        if (output > 1.0) {
            output = 1.0;
        }
        if (output < -1.0) {
            output = -1.0;
        }
        return output;
    }
    
    void changeDistortionAmt(double newDistortion) {
        alpha = newDistortion;
    }
};

#endif /* Distortion_hpp */
