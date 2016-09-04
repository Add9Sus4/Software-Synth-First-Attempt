//
//  SampleEffectProcessingChain.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/30/16.
//
//  This class represents a chain of effects, each of which must be a subclass of SampleEffect,
//  which means that it processes audio one sample at a time.

#ifndef ProcessingChain_hpp
#define ProcessingChain_hpp

#include <stdio.h>
#include <vector>
#include "SampleEffect.hpp"

class SampleEffectProcessingChain {
private:
    std::vector<SampleEffect *> effects; // Vector containing all the effects in this chain
    
public:
    double process(double sample); // Processes a sample using all the effects in the chain.
    void addEffect(SampleEffect *effect); // Adds an effect to the vector of effects
};

#endif /* ProcessingChain_hpp */
