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
#include "OscillatorGroup.hpp"
#include "SpectralFilter.hpp"

typedef enum EffectID {
    kOscillatorGroup1,
    kOscillatorGroup2,
    kBiquadFilter1,
    kBiquadFilter2,
    kSpectralFilter1,
    kSpectralFilter2,
    kFormantFilter1,
    kFormantFilter2,
    kChorus1,
    kChorus2,
    kFlanger1,
    kFlanger2
} EffectID;

typedef enum ModulatorID {
    kLfo1,
    kLfo2,
    kLfo3,
    kLfo4,
    kAmpEnvelope,
    kModEnvelope1,
    kModEnvelope2,
    kModEnvelope3
} ModulatorID;

class Voice {
public:
    Voice() {
        
        chain = new BlockEffectProcessingChain();
        
        // Create all effects
        oscillatorGroup1 = new OscillatorGroup();
        oscillatorGroup1->setId(kOscillatorGroup1);
        oscillatorGroup2 = new OscillatorGroup();
        oscillatorGroup1->setId(kOscillatorGroup2);
        biquadFilter1 = new BiquadFilter();
        biquadFilter1->setId(kBiquadFilter1);
        biquadFilter2 = new BiquadFilter();
        biquadFilter2->setId(kBiquadFilter2);
        spectralFilter1 = new SpectralFilter();
        spectralFilter1->setId(kSpectralFilter1);
        spectralFilter2 = new SpectralFilter();
        spectralFilter2->setId(kSpectralFilter2);
        formantFilter1 = new BlockFormantFilter();
        formantFilter1->setId(kFormantFilter1);
        formantFilter2 = new BlockFormantFilter();
        formantFilter2->setId(kFormantFilter2);
        chorus1 = new Chorus();
        chorus1->setId(kChorus1);
        chorus2 = new Chorus();
        chorus2->setId(kChorus2);
        flanger1 = new BlockFlanger();
        flanger1->setId(kFlanger1);
        flanger2 = new BlockFlanger();
        flanger2->setId(kFlanger2);
        
        // Create all modulators
        lfo1 = new LFO();
        lfo1->setId(kLfo1);
        lfo2 = new LFO();
        lfo2->setId(kLfo2);
        lfo3 = new LFO();
        lfo3->setId(kLfo3);
        lfo4 = new LFO();
        lfo4->setId(kLfo4);
        ampEnvelope = new Envelope();
        ampEnvelope->setId(kAmpEnvelope);
        modEnvelope1 = new Envelope();
        modEnvelope1->setId(kModEnvelope1);
        modEnvelope2 = new Envelope();
        modEnvelope2->setId(kModEnvelope2);
        modEnvelope3 = new Envelope();
        modEnvelope3->setId(kModEnvelope3);

        // Add all effects to the unusedEffects vector
        unusedEffects.push_back(oscillatorGroup1);
        unusedEffects.push_back(oscillatorGroup2);
        unusedEffects.push_back(biquadFilter1);
        unusedEffects.push_back(biquadFilter2);
        unusedEffects.push_back(spectralFilter1);
        unusedEffects.push_back(spectralFilter2);
        unusedEffects.push_back(formantFilter1);
        unusedEffects.push_back(formantFilter2);
        unusedEffects.push_back(chorus1);
        unusedEffects.push_back(chorus2);
        unusedEffects.push_back(flanger1);
        unusedEffects.push_back(flanger2);
        
        // Add all unused modulators to the unusedModulators vector
        unusedModulators.push_back(lfo1);
        unusedModulators.push_back(lfo2);
        unusedModulators.push_back(lfo3);
        unusedModulators.push_back(lfo4);
        unusedModulators.push_back(ampEnvelope);
        unusedModulators.push_back(modEnvelope1);
        unusedModulators.push_back(modEnvelope2);
        unusedModulators.push_back(modEnvelope3);

    }
private:
    BlockEffectProcessingChain* chain;
    
    /*
     All effects should be declared here!
     */
    OscillatorGroup* oscillatorGroup1;
    OscillatorGroup* oscillatorGroup2;
    BiquadFilter* biquadFilter1;
    BiquadFilter* biquadFilter2;
    SpectralFilter* spectralFilter1;
    SpectralFilter* spectralFilter2;
    BlockFormantFilter* formantFilter1;
    BlockFormantFilter* formantFilter2;
    Envelope* ampEnvelope;
    Envelope* modEnvelope1;
    Envelope* modEnvelope2;
    Envelope* modEnvelope3;
    LFO* lfo1;
    LFO* lfo2;
    LFO* lfo3;
    LFO* lfo4;
    Chorus* chorus1;
    Chorus* chorus2;
    BlockFlanger* flanger1;
    BlockFlanger* flanger2;
    
    /*
     
     This vector contains all the effects that are available to be added to the processing chain.
     All effects start out in this vector. If an effect is added to the chain, it is removed
     from the vector. If it is removed from the chain, it is added back into the vector.
     
     The available effects include:
     
     2x OscillatorGroup
     2x BiquadFilter
     2x SpectralFilter
     2x FormantFilter
     1x AmpEnvelope
     3x ModEnvelope
     4x LFO
     2x Chorus
     2x Flanger
     
     */
    std::vector<BlockEffect*> unusedEffects;
    std::vector<Modulator*> unusedModulators;
};

#endif /* Voice_hpp */
