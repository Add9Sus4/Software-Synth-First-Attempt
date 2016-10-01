//
//  Voice.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/23/16.
//
//

#ifndef Voice_hpp
#define Voice_hpp

#include <iostream>
#include <stdio.h>
#include <vector>

#include "BiquadFilter.hpp"
#include "BlockEffect.hpp"
#include "BlockEffectProcessingChain.hpp"
#include "BlockFlanger.hpp"
#include "BlockFormantFilter.hpp"
#include "Chorus.hpp"
#include "Envelope.hpp"
#include "LFO.hpp"
#include "Model.hpp"
#include "OscillatorGroup.hpp"
#include "SpectralFilter.hpp"

class Voice {
public:
    Voice(Model* model, int index) {
        
        chain = new BlockEffectProcessingChain();

        // Add all effects to the unusedEffects vector
        unusedEffects.push_back(model->oscillatorGroup1[index]);
        unusedEffects.push_back(model->oscillatorGroup2[index]);
        unusedEffects.push_back(model->biquadFilter1[index]);
        unusedEffects.push_back(model->biquadFilter2[index]);
        unusedEffects.push_back(model->spectralFilter1[index]);
        unusedEffects.push_back(model->spectralFilter2[index]);
        unusedEffects.push_back(model->formantFilter1[index]);
        unusedEffects.push_back(model->formantFilter2[index]);
        unusedEffects.push_back(model->chorus1[index]);
        unusedEffects.push_back(model->chorus2[index]);
        unusedEffects.push_back(model->flanger1[index]);
        unusedEffects.push_back(model->flanger2[index]);
        
        // Add all unused modulators to the unusedModulators vector
        unusedModulators.push_back(model->lfo1[index]);
        unusedModulators.push_back(model->lfo2[index]);
        unusedModulators.push_back(model->lfo3[index]);
        unusedModulators.push_back(model->lfo4[index]);
        unusedModulators.push_back(model->ampEnvelope[index]);
        unusedModulators.push_back(model->modEnvelope1[index]);
        unusedModulators.push_back(model->modEnvelope2[index]);
        unusedModulators.push_back(model->modEnvelope3[index]);

    }
    
    BlockEffect* getEffectByControlParamIdx(int paramIndex) {
        BlockEffect* effect;
        for (int i=0; i<unusedEffects.size(); i++) {
            if (unusedEffects[i]->getId() == paramIndex) {
                effect = unusedEffects[i];
                break;
            }
        }
        return effect;
    }
    
    void addEffect(int effectId) {
        BlockEffect* effect;
        for (int i=0; i<unusedEffects.size(); i++) {
            if (unusedEffects[i]->getId() == effectId) {
                effect = unusedEffects[i];
                break;
            }
        }
        chain->addEffect(effect);
        effect->setActive(true);
    }
    
    double** process(double** outBlock, int blockSize) {
        outBlock = chain->process(outBlock, blockSize);
        return outBlock;
    }
    
private:
    BlockEffectProcessingChain* chain;
    
    /*
     This vector contains all the effects that are available to be added to the processing chain.
     All effects start out in this vector. If an effect is added to the chain, it is removed
     from the vector. If it is removed from the chain, it is added back into the vector.
     */
    std::vector<BlockEffect*> unusedEffects;
    std::vector<Modulator*> unusedModulators;
};

#endif /* Voice_hpp */
