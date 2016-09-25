//
//  VoiceManager.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/23/16.
//
//

#ifndef VoiceManager_hpp
#define VoiceManager_hpp

#define MAX_VOICES  16

#include <stdio.h>

#include "BlockEffect.hpp"
#include "Voice.hpp"

class VoiceManager : public BlockEffect {
public:
    VoiceManager() {
        voices = new Voice[MAX_VOICES + 1];
    }
    double** process(double** outBlock, int blockSize) {
        
        for (int i=0; i<blockSize; i++) {
            outBlock[LEFT][i] = 0.0;
            outBlock[RIGHT][i] = 0.0;
        }
        
        outBlock = voices[0].process(outBlock, blockSize);
        
        return outBlock;
    }
    void addEffect(EffectID effectId) {
        for (int i=0; i<MAX_VOICES + 1; i++) {
            voices[i].addEffect(effectId);
        }
    }
private:
    Voice *voices;
};

#endif /* VoiceManager_hpp */
