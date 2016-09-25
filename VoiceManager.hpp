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
        return outBlock;
    }
private:
    Voice *voices;
};

#endif /* VoiceManager_hpp */
