//
//  VoiceManager.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/23/16.
//
//

#ifndef VoiceManager_hpp
#define VoiceManager_hpp

#include <stdio.h>
#include <vector>

#include "BlockEffect.hpp"
#include "Model.hpp"
#include "Voice.hpp"

class VoiceManager : public BlockEffect {
public:
    VoiceManager(Model* model) {
        for (int i=0; i<MAX_VOICES+1; i++) {
            std::cout << "adding new voice" << std::endl;
           voices.push_back(new Voice(model, i));
        }
        std::cout << "voices size: " << voices.size() << std::endl;
        this->model = model;
    }
    double** process(double** outBlock, int blockSize) {
        
        for (int i=0; i<blockSize; i++) {
            outBlock[LEFT][i] = 0.0;
            outBlock[RIGHT][i] = 0.0;
        }
        
        outBlock = voices[0]->process(outBlock, blockSize);
        
        return outBlock;
    }
    
    BlockEffect* getEffectByControlParamIdx(int paramIndex) {
        return voices[0]->getEffectByControlParamIdx(paramIndex);
    }
    
    void addEffect(int effectId) {
        for (int i=0; i<MAX_VOICES + 1; i++) {
            voices[i]->addEffect(effectId);
        }
    }
    
    void drawSlotView(IRECT rect) {
        
    }
private:
    std::vector<Voice*> voices;
    Model* model;
};

#endif /* VoiceManager_hpp */
