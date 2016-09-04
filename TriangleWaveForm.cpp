//
//  TriangleWaveForm.cpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/28/16.
//
//

#include "TriangleWaveForm.hpp"

void TriangleWaveForm::initializeWaveForm(int length) {
    samples = new double[length];
    for (int i=0; i<length/4; i++) {
        samples[i] = 0.0 + 1.0*4*i/(double)length;
    }
    for (int i=length/4; i<length/2; i++) {
        samples[i] = 1.0 - 1.0*4*i/(double)length;
    }
    for (int i=length/2; i<length*3/4; i++) {
        samples[i] = 0.0 - 1.0*4*i/(double)length;
    }
    for (int i=length*3/4; i<length; i++) {
        samples[i] = -1.0 + 1.0*4*i/(double)length;
    }
}