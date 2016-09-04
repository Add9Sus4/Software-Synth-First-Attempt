//
//  NoiseWaveForm.cpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/28/16.
//
//

#include "NoiseWaveForm.hpp"
#include <stdlib.h>
#include <time.h>

void NoiseWaveForm::initializeWaveForm(int length) {
    srand (time(NULL));
    samples = new double[length];
    for (int i=0; i<length; i++) {
        samples[i] = ((double)(rand() % 1000)/999.0)*2.0 - 1.0;
    }
}