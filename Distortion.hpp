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
    double process(double sample);
};

#endif /* Distortion_hpp */
