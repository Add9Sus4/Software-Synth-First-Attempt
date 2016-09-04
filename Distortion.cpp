//
//  Distortion.cpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/31/16.
//
//

#include "Distortion.hpp"

double Distortion::process(double sample) {
    return(sample /fabs(sample))*(1 - exp(alpha*pow(sample, 2)/fabs(sample)));
}