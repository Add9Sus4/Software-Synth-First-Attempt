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

void Phasor::setPhase(WavePhase wavePhase) {
    // Set phase to 0 if sync is selected
    if (wavePhase == WavePhase::SYNC) {
        phase = 0.0;
    } else {
        // Set phase randomly if free is selected
        phase = ((double)(rand() % 1000)/999.0);
    }
}