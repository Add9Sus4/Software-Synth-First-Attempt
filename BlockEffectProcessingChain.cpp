//
//  BlockEffectProcessingChain.cpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/1/16.
//
//

#include "BlockEffectProcessingChain.hpp"

void BlockEffectProcessingChain::addEffect(BlockEffect *effect) {
    effects.push_back(effect);
}

void BlockEffectProcessingChain::process(double *inBlock, double *outBlock, int blockSize) {
    for(std::vector<int>::size_type i = 0; i != effects.size(); i++) {
        effects[i]->process(inBlock, inBlock, blockSize);
    }
    for (int i=0; i<blockSize; i++) {
        outBlock[i] = inBlock[i];
    }
}