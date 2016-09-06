//
//  Phasor.cpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/28/16.
//
//

#include "Phasor.hpp"
void Phasor::incrementPhase() {
    phase += frequency/(double)SAMPLE_RATE;
    if (phase > 1.0) phase -= 1.0;
}