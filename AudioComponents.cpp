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
  
  kOsc,
  
  kNumParams
};

enum ELayout
{
  kWidth = GUI_WIDTH,
  kHeight = GUI_HEIGHT,
  
  kViewTypeAreaLeftBound = 0,
  kViewTypeAreaUpperBound = 0,
  kViewTypeAreaRightBound = GUI_WIDTH,
  kViewTypeAreaLowerBound = 80,
  
  kElementSelectAreaLeftBound = 0,
  kElementSelectAreaUpperBound = 80,
  kElementSelectAreaRightBound = 240,
  kElementSelectAreaLowerBound = 480,
  
  kModulatorViewAreaLeftBound = 720,
  kModulatorViewAreaUpperBound = 80,
  kModulatorViewAreaRightBound = GUI_WIDTH,
  kModulatorViewAreaLowerBound = 480,
  
  kElementChainAreaLeftBound = 0,
  kElementChainAreaUpperBound = 480,
  kElementChainAreaRightBound = GUI_WIDTH,
  kElementChainAreaLowerBound = GUI_HEIGHT,
  
  kMainViewAreaLeftBound = 240,
  kMainViewAreaUpperBound = 80,
  kMainViewAreaRightBound = 720,
  kMainViewAreaLowerBound = 480
};

/* CONSTRUCTOR */
AudioComponents::AudioComponents(IPlugInstanceInfo instanceInfo)
  :	IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo), mGain(1.)
{
  TRACE;
  
  /* --------------------------INITIALIZE THE PARAMETERS ---------------------------
   
   Parameters are initialized here.
   
   ----------------------------------------------------------------------------------*/

  GetParam(kOsc)->InitBool("Osc", 0);
  
  /* --------------------------CREATE THE PROCESSING CHAINS ---------------------------   
   
              Effects must be added to the chain in order to affect the sound.
              Each effect will be called in the order it was added to the chain.
   
   ----------------------------------------------------------------------------------*/
  
  // Voice Manager
  voiceManager = new VoiceManager();
  
  /* --------------------------CREATE THE GRAPHICS ---------------------------
   ----------------------------------------------------------------------------------*/
  
  // Create graphics
  IGraphics* pGraphics = MakeGraphics(this, kWidth, kHeight);
  
  // Handle mouseover
  pGraphics->HandleMouseOver(true);
  
  // Different sections of the overall view area
  viewTypeArea = new ViewTypeArea(this, IRECT(kViewTypeAreaLeftBound, kViewTypeAreaUpperBound, kViewTypeAreaRightBound, kViewTypeAreaLowerBound));
  
  elementSelectArea = new ElementSelectArea(this, IRECT(kElementSelectAreaLeftBound, kElementSelectAreaUpperBound, kElementSelectAreaRightBound, kElementSelectAreaLowerBound));
  
  modulatorViewArea = new ModulatorViewArea(this, IRECT(kModulatorViewAreaLeftBound, kModulatorViewAreaUpperBound, kModulatorViewAreaRightBound, kModulatorViewAreaLowerBound));
  
  elementChainArea = new ElementChainArea(this, IRECT(kElementChainAreaLeftBound, kElementChainAreaUpperBound, kElementChainAreaRightBound, kElementChainAreaLowerBound));
  
  mainViewArea = new MainViewArea(this, IRECT(kMainViewAreaLeftBound, kMainViewAreaUpperBound, kMainViewAreaRightBound, kMainViewAreaLowerBound));
  
  // Knobs, sliders, other controls
  IBitmap osc = pGraphics->LoadIBitmap(OSC_ID, OSC_FN, 2);
  //  IBitmap knob = pGraphics->LoadIBitmap(KNOB4_ID, KNOB4_FN, 60); // Knob bitmap
  
  pGraphics->AttachControl(viewTypeArea);
  pGraphics->AttachControl(elementSelectArea);
  pGraphics->AttachControl(modulatorViewArea);
  pGraphics->AttachControl(elementChainArea);
  pGraphics->AttachControl(mainViewArea);
  pGraphics->AttachControl(new ISwitchControl(this, 5, kElementSelectAreaUpperBound + 10, kOsc, &osc));

  // Background
  pGraphics->AttachPanelBackground(&COLOR_BLACK);
  
  AttachGraphics(pGraphics);

  //MakePreset("preset 1", ... );
  MakeDefaultPreset((char *) "-", kNumPrograms);
}

AudioComponents::~AudioComponents() {}

void AudioComponents::ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames)
{
  outputs = voiceManager->process(outputs, nFrames);
  
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
    case kOsc:
      if ((int)GetParam(kOsc)->Value() == 1) {
        elementChainArea->highlightNextSlot(SlotMode::HIGHLIGHTED);
//        GetGUI()->GetControl(5)->Hide(true);
      } else {
        elementChainArea->highlightNextSlot(SlotMode::EMPTY);
//        GetGUI()->GetControl(5)->Hide(false);
      }
      break;
      default:
      break;
  }
}

void AudioComponents::connectModulator(Modulator* modulator, Parameter* parameter) {
  parameter->addModulator(modulator);
}
