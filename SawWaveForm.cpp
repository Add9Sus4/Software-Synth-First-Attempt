//
//  SawWaveForm.cpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/28/16.
//
//

#include "SawWaveForm.hpp"

void SawWaveForm::initializeWaveForm(int length) {
    samples = new double[length];
    for (int i=0; i<length; i++) {
        samples[i] = -1.0 + 2.0*i/(double)length;
    }
}