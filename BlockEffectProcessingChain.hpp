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

class BlockEffectProcessingChain : public BlockEffect {
private:
    std::vector<BlockEffect*> effects; // Vector containing all the effects in this chain
    
public:
    // Processes a sample using all the effects in the chain.
    double** process(double** outBlock, int blockSize) {
        
        // If the chain has at least one effect, get output from chain
        if (effects.size() > 0) {
            outBlock = effects.back()->getSamples(outBlock, blockSize);
        }
        // Otherwise, return zeros
        else {
            outBlock[LEFT] = new double[blockSize];
            outBlock[RIGHT] = new double[blockSize];
            for (int i=0; i<blockSize; i++) {
                outBlock[LEFT][i] = 0.0;
                outBlock[RIGHT][i] = 0.0;
            }
        }
        
        return outBlock;
    }
    
    // Adds an effect to the vector of effects
    void addEffect(BlockEffect* effect) {
        
        // Add the last effect in the vector as an input for this new effect
        if (effects.size() > 0) {
            effect->addInput(effects.back());
        }
        
        // Add the effect to the vector
        effects.push_back(effect);
    }};

#endif /* BlockEffectProcessingChain_hpp */
