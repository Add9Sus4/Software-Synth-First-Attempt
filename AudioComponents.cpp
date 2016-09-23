#include "AudioComponents.h"
#include "IPlug_include_in_plug_src.h"
#include "IControl.h"
#include "resource.h"

#define HEIGHT_INC  100

const int kNumPrograms = 1;

enum EParams
{
  kGain = 0,
  kWaveform,
  kPhaseMode,
  kDetune,
  kPan,
  
  kOsc1Sine,
  kOsc1Saw,
  kOsc1Tri,
  kOsc1Square,
  kOsc1Pulse,
  kOsc1Noise,
  
  kFader_Vert,
  
  kDistortionAmt,
  
  kAttack,
  kDecay,
  kSustain,
  kRelease,
  
  kFilterAttack,
  kFilterDecay,
  kFilterSustain,
  kFilterRelease,
  
  kFilterCutoff,
  
  kFilterModAmt,
  
  kNumParams
};

enum ELayout
{
  kWidth = GUI_WIDTH,
  kHeight = GUI_HEIGHT,

  kGainX = 25,
  kGainY = 25,
  
  kDetuneX = 25,
  kDetuneY = 300,
  
  kPanX = 125,
  kPanY = 350,
  
  kFilterCutoffX = 200,
  kFilterCutoffY = 350,
  
  kWaveformX = 25,
  kWaveformY = 350,
  
  kPhaseModeX = 25,
  kPhaseModeY = 400,
  
  kAttackX = 400,
  kAttackY = 25,
  kDecayX = 450,
  kDecayY = 25,
  kSustainX = 500,
  kSustainY = 25,
  kReleaseX = 550,
  kReleaseY = 25,
  
  kFilterAttackX = 400,
  kFilterAttackY = 125,
  kFilterDecayX = 450,
  kFilterDecayY = 125,
  kFilterSustainX = 500,
  kFilterSustainY = 125,
  kFilterReleaseX = 550,
  kFilterReleaseY = 125,
  
  kKnobFrames = 60
};

/* CONSTRUCTOR */
AudioComponents::AudioComponents(IPlugInstanceInfo instanceInfo)
  :	IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo), mGain(1.)
{
  TRACE;
  
  /* --------------------------INITIALIZE THE PARAMETERS ---------------------------
   
   Parameters are initialized here.
   
   ----------------------------------------------------------------------------------*/
  
  oscillatorGroup = new OscillatorGroup(16, Bb_1, WaveType::SAW);
  biquadFilter = new BiquadFilter(LPF, 0.0, 500, SAMPLE_RATE, 2);
  blockFormantFilter = new BlockFormantFilter(Vowel::U);
  chorus = new Chorus(512, 6, 800, 0.3, 0.25);
  blockDistortion = new BlockDistortion(DistortionType::DISTORTION);
  blockFlanger = new BlockFlanger(75, 0.5, 0.3, 0.85, WaveType::SINE);
  spectralFilter = new SpectralFilter(512);
  
  lfo = new LFO(1.0);
  connectModulator(lfo, biquadFilter->getParam(FREQUENCY));
  
  /* --------------------------CREATE THE PROCESSING CHAINS ---------------------------   
   
              Effects must be added to the chain in order to affect the sound.
              Each effect will be called in the order it was added to the chain.
   
   ----------------------------------------------------------------------------------*/
  
  // Sample Processing Chains
  
  // Block Processing Chains
  mainProcessingChain = new BlockEffectProcessingChain();
  mainProcessingChain->addEffect(oscillatorGroup);
//  mainProcessingChain->addEffect(blockFormantFilter);
//  mainProcessingChain->addEffect(blockFlanger);
//  mainProcessingChain->addEffect(chorus);
  mainProcessingChain->addEffect(biquadFilter);
//  mainProcessingChain->addEffect(blockDistortion);
//  mainProcessingChain->addEffect(spectralFilter);
  
//  mainProcessingChain->addEffect(chorus);
  
  /* --------------------------CREATE THE GRAPHICS ---------------------------
   ----------------------------------------------------------------------------------*/
  
  // Create graphics
  IGraphics* pGraphics = MakeGraphics(this, kWidth, kHeight);
  
  // Bitmaps for all the images
//  IBitmap knob = pGraphics->LoadIBitmap(KNOB4_ID, KNOB4_FN, kKnobFrames); // Knob bitmap
  
  // Background
  pGraphics->AttachBackground(BACKGROUND3_ID, BACKGROUND3_FN);
  
  AttachGraphics(pGraphics);

  //MakePreset("preset 1", ... );
  MakeDefaultPreset((char *) "-", kNumPrograms);
}

AudioComponents::~AudioComponents() {}

void AudioComponents::ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames)
{
  outputs = mainProcessingChain->process(outputs, nFrames);
}

/*
 *  Processes all midi messages
 */
void AudioComponents::ProcessMidiMsg(IMidiMsg *pMsg) {
  IMidiMsg::EStatusMsg status = pMsg->StatusMsg();
  
  // Note on message received
  if(status == IMidiMsg::kNoteOn) {

    // Note off message received
  } else if (status == IMidiMsg::kNoteOff) {

  }
}

void AudioComponents::Reset()
{
  TRACE;
  IMutexLock lock(this);
}

void AudioComponents::OnParamChange(int paramIdx)
{
  IMutexLock lock(this);

  switch (paramIdx)
  {
      default:
      break;
  }
}

void AudioComponents::connectModulator(Modulator* modulator, Parameter* parameter) {
  parameter->addModulator(modulator);
}
