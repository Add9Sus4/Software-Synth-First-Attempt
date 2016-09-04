//
//  SampleDelay.cpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/28/16.
//
//

#include "SampleDelay.hpp"
double SampleDelay::process(double sample) {
    data[length-1] = sample;
    data[length-1] += data[0]*feedback;
    for (int i=0; i<length-1; i++) {
        data[i] = data[i+1];
    }
    
    return data[0] + sample;
}