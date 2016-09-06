//
//  BlockEffectProcessingChain.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/1/16.
//
//

#ifndef BlockEffectProcessingChain_hpp
#define BlockEffectProcessingChain_hpp

#include <stdio.h>
#include <vector>
#include "BlockEffect.hpp"

class BlockEffectProcessingChain {
private:
    std::vector<BlockEffect *> effects; // Vector containing all the effects in this chain
    
public:
    void process(double *inBlock, double *outBlock, int blockSize); // Processes a sample using all the effects in the chain.
    void addEffect(BlockEffect *effect) {
          effects.push_back(effect);
    }// Adds an effect to the vector of effects
};

#endif /* BlockEffectProcessingChain_hpp */
