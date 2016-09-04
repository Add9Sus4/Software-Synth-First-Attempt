#ifndef __AUDIOCOMPONENTS__
#define __AUDIOCOMPONENTS__

#include "IPlug_include_in_plug_hdr.h"
#include "OscillatorGroup.hpp"
#include "Filter.hpp"
#include "SampleDelay.hpp"
#include "BlockDelay.hpp"
#include "SampleEffectProcessingChain.hpp"
#include "Flanger.hpp"
#include "Distortion.hpp"
#include "SymmetricalSoftClip.hpp"
#include "Chorus.hpp"
#include "BlockEffectProcessingChain.hpp"
#include "Symphony.hpp"

class AudioComponents : public IPlug
{
public:
  AudioComponents(IPlugInstanceInfo instanceInfo);
  ~AudioComponents();

  void Reset();
  void OnParamChange(int paramIdx);
  void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);
  void ProcessMidiMsg(IMidiMsg *pMsg);

private:
  double mGain;
  SampleDelay *delayLeft;
  SampleDelay *delayRight;
  OscillatorGroup *oscillatorGroup;
  Filter *filterLeft;
  Filter *filterRight;
  Oscillator *LFOLeft;
  Oscillator *LFORight;
  FormantFilter *formantFilterLeft;
  FormantFilter *formantFilterRight;
  BlockDelay *blockDelayLeft;
  BlockDelay *blockDelayRight;
  BlockDelay *blockDelayLeft2;
  BlockDelay *blockDelayRight2;
  SampleEffectProcessingChain *processingChainLeft;
  SampleEffectProcessingChain *processingChainRight;
  BlockEffectProcessingChain *blockProcessingChainLeft;
  BlockEffectProcessingChain *blockProcessingChainRight;
  Flanger *flangerLeft;
  Flanger *flangerRight;
  Distortion *distortionLeft;
  Distortion *distortionRight;
  SymmetricalSoftClip *softClipLeft;
  SymmetricalSoftClip *softClipRight;
  Chorus *chorusLeft;
  Chorus *chorusRight;
  Symphony *symphony;
  bool flag;
  IMidiMsg *midiMsg;
  int cycleInterval;
  int count;
};

#endif
