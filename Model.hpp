//
//  Model.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/26/16.
//
//

#ifndef Model_hpp
#define Model_hpp

#define MAX_VOICES  16

#include <stdio.h>

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
#include "resource.h"

enum Controls
{
    
    // Draggable icons
    kOsc1,
    kOsc2,
    kBqf1,
    kBqf2,
    kCho1,
    kCho2,
    kEnva,
    kEnv1,
    kEnv2,
    kEnv3,
    kFln1,
    kFln2,
    kFmf1,
    kFmf2,
    kLfoo1,
    kLfoo2,
    kLfoo3,
    kLfoo4,
    kSpf1,
    kSpf2,
    
    
    kKnob,
    kPan,
    kVolume,
    
    kNumControls
};

class Model {
public:
    Model() {
        for (int i=0; i<MAX_VOICES+1; i++) {
            oscillatorGroup1[i] = new OscillatorGroup(16, 100.0, WaveType::SAW);
            oscillatorGroup1[i]->setId(kOsc1);
            oscillatorGroup2[i] = new OscillatorGroup(16, 100.0, WaveType::SAW);
            oscillatorGroup2[i]->setId(kOsc2);
            biquadFilter1[i] = new BiquadFilter(LPF, 0.0, 500, SAMPLE_RATE, 2);
            biquadFilter1[i]->setId(kBqf1);
            biquadFilter2[i] = new BiquadFilter(LPF, 0.0, 500, SAMPLE_RATE, 2);
            biquadFilter2[i]->setId(kBqf2);
            spectralFilter1[i] = new SpectralFilter(512);
            spectralFilter1[i]->setId(kSpf1);
            spectralFilter2[i] = new SpectralFilter(512);
            spectralFilter2[i]->setId(kSpf2);
            formantFilter1[i] = new BlockFormantFilter(Vowel::O);
            formantFilter1[i]->setId(kFmf1);
            formantFilter2[i] = new BlockFormantFilter(Vowel::O);
            formantFilter2[i]->setId(kFmf2);
            chorus1[i] = new Chorus(512, 6, 800, 0.3, 0.1);
            chorus1[i]->setId(kCho1);
            chorus2[i] = new Chorus(512, 6, 800, 0.3, 0.1);
            chorus2[i]->setId(kCho2);
            flanger1[i] = new BlockFlanger(75, 0.5, 0.3, 0.85, WaveType::SINE);
            flanger1[i]->setId(kFln1);
            flanger2[i] = new BlockFlanger(75, 0.5, 0.3, 0.85, WaveType::SINE);
            flanger2[i]->setId(kFln2);
            
            lfo1[i] = new LFO(1.0);
            lfo1[i]->setId(kLfoo1);
            lfo2[i] = new LFO(1.0);
            lfo2[i]->setId(kLfoo2);
            lfo3[i] = new LFO(1.0);
            lfo3[i]->setId(kLfoo3);
            lfo4[i] = new LFO(1.0);
            lfo4[i]->setId(kLfoo4);
            ampEnvelope[i] = new Envelope();
            ampEnvelope[i]->setId(kEnva);
            modEnvelope1[i] = new Envelope();
            modEnvelope1[i]->setId(kEnv1);
            modEnvelope2[i] = new Envelope();
            modEnvelope2[i]->setId(kEnv2);
            modEnvelope3[i] = new Envelope();
            modEnvelope3[i]->setId(kEnv3);
        }
    }
    
    void loadGUIElements(IGraphics* pGraphics, IPlugBase* pPlug) {
        IBitmap knob = pGraphics->LoadIBitmap(KNOB4_ID, KNOB4_FN, 60);
        IBitmap fader = pGraphics->LoadIBitmap(FADER2_ID, FADER2_FN, 60);
        oscillatorGroup1[0]->knobControl = new IKnobMultiControl(pPlug, -100, -100, kKnob, &knob);
        oscillatorGroup1[0]->panControl = new IKnobMultiControl(pPlug, -100, -100, kPan, &knob);
        oscillatorGroup1[0]->volumeFader = new IKnobMultiControl(pPlug, -100, -100, kVolume, &fader);
        pGraphics->AttachControl(oscillatorGroup1[0]->knobControl);
        pGraphics->AttachControl(oscillatorGroup1[0]->panControl);
        pGraphics->AttachControl(oscillatorGroup1[0]->volumeFader);
        oscillatorGroup1[0]->knobControl->Hide(true);
        oscillatorGroup1[0]->panControl->Hide(true);
        oscillatorGroup1[0]->volumeFader->Hide(true);
        oscillatorGroup1[0]->knobControl->move(-100, -100);
        oscillatorGroup1[0]->panControl->move(-100, -100);
        oscillatorGroup1[0]->volumeFader->move(-100, -100);
    }
    
    OscillatorGroup* oscillatorGroup1[MAX_VOICES+1];
    OscillatorGroup* oscillatorGroup2[MAX_VOICES+1];
    BiquadFilter* biquadFilter1[MAX_VOICES+1];
    BiquadFilter* biquadFilter2[MAX_VOICES+1];
    SpectralFilter* spectralFilter1[MAX_VOICES+1];
    SpectralFilter* spectralFilter2[MAX_VOICES+1];
    BlockFormantFilter* formantFilter1[MAX_VOICES+1];
    BlockFormantFilter* formantFilter2[MAX_VOICES+1];
    Envelope* ampEnvelope[MAX_VOICES+1];
    Envelope* modEnvelope1[MAX_VOICES+1];
    Envelope* modEnvelope2[MAX_VOICES+1];
    Envelope* modEnvelope3[MAX_VOICES+1];
    LFO* lfo1[MAX_VOICES+1];
    LFO* lfo2[MAX_VOICES+1];
    LFO* lfo3[MAX_VOICES+1];
    LFO* lfo4[MAX_VOICES+1];
    Chorus* chorus1[MAX_VOICES+1];
    Chorus* chorus2[MAX_VOICES+1];
    BlockFlanger* flanger1[MAX_VOICES+1];
    BlockFlanger* flanger2[MAX_VOICES+1];
private:


};

//2x OscillatorGroup
//2x BiquadFilter
//2x SpectralFilter
//2x FormantFilter
//1x AmpEnvelope
//3x ModEnvelope
//4x LFO
//2x Chorus
//2x Flanger

#endif /* Model_hpp */
