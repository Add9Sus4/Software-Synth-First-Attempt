//
//  ProcessingChain.cpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/30/16.
//
//

#include "SampleEffectProcessingChain.hpp"


void SampleEffectProcessingChain::addEffect(SampleEffect *effect) {
    effects.push_back(effect);
}

double SampleEffectProcessingChain::process(double sample) {
    double newSample = sample;
    for(std::vector<int>::size_type i = 0; i != effects.size(); i++) {
        newSample = effects[i]->process(newSample);
    }
    return newSample;
}