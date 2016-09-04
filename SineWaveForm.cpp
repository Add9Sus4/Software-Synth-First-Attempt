//
//  SineWaveForm.cpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/28/16.
//
//

#include "SineWaveForm.hpp"
#include "math.h"

#define PI 3.14159265358979323846264338327950

void SineWaveForm::initializeWaveForm(int length) {
    samples = new double[length];
    for (int i=0; i<length; i++) {
        samples[i] = sin(i*2*PI/(double)length);
    }
}