#ifndef __AUDIOCOMPONENTS__
#define __AUDIOCOMPONENTS__

#include <stdlib.h>
#include <string>

#include "IPlug_include_in_plug_hdr.h"

#include "BiquadFilter.hpp"
#include "BlockDelay.hpp"
#include "BlockDistortion.hpp"
#include "BlockEffectProcessingChain.hpp"
#include "BlockFlanger.hpp"
#include "BlockFormantFilter.hpp"
#include "Chorus.hpp"
#include "Distortion.hpp"
#include "EnvelopeOpenGL.hpp"
#include "Filter.hpp"
#include "FilterEnvelopeOpenGL.hpp"
#include "Flanger.hpp"
#include "LFO.hpp"
#include "Model.hpp"
#include "Modulator.hpp"
#include "OscillatorGroup.hpp"
#include "OpenGLTestClass.hpp"
#include "Parameter.hpp"
#include "SampleDelay.hpp"
#include "SampleEffectProcessingChain.hpp"
#include "SpectralFilter.hpp"
#include "SymmetricalSoftClip.hpp"
#include "Transform.hpp"
#include "ViewManager.hpp"
#include "VoiceManager.hpp"

class AudioComponents : public IPlug
{
public:
  AudioComponents(IPlugInstanceInfo instanceInfo);
  ~AudioComponents();

  void Reset();
  void OnParamChange(int paramIdx);
  void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);
  void ProcessMidiMsg(IMidiMsg *pMsg);
  
  void connectModulator(Modulator* modulator, Parameter* parameter);

private:
  double mGain;
  
  ViewBottom* elementChainArea;
  ViewLeft* elementSelectArea;
  ViewCenter* mainViewArea;
  ViewRight* modulatorViewArea;
  ViewTop* viewTypeArea;
  
  VoiceManager* voiceManager;
  
  ViewManager* viewManager;
  
  Model* model;
};

#endif
