#include "AudioComponents.h"
#include "IPlug_include_in_plug_src.h"
#include "IControl.h"
#include "resource.h"

#define HEIGHT_INC  100

const int kNumPrograms = 1;

enum EParams {
  kNumParams
};

/* CONSTRUCTOR */
AudioComponents::AudioComponents(IPlugInstanceInfo instanceInfo)
  :	IPLUG_CTOR(kNumControls, kNumPrograms, instanceInfo), mGain(1.)
{
  TRACE;
  
  GetParam(kKnob)->InitDouble("Knob", 0.5, 0.0, 1.0, 0.01);
  GetParam(kPan)->InitDouble("Pan", 0.5, 0.01, 1.0, 0.01);
  GetParam(kVolume)->InitDouble("Volume", 1.0, 0.0, 1.0, 0.01);
  GetParam(kVolume)->SetShape(2.0);
  
  // Create graphics
  IGraphics* pGraphics = MakeGraphics(this, GUI_WIDTH, GUI_HEIGHT);
  
  // Handle mouseover
  pGraphics->HandleMouseOver(true);
  
  // Model (this contains all the effects and modulators for the entire plugin)
  model = new Model();
  
  // Voice Manager
  voiceManager = new VoiceManager(model);
  
  // View manager (handles views for the plugin)
  viewManager = new ViewManager(this, voiceManager);
  viewManager->attachControls(pGraphics);
  
  // Knobs
//  IBitmap knob = pGraphics->LoadIBitmap(KNOB_ID, KNOB_FN, 60);
//  IKnobMultiControl* knobControl = new IKnobMultiControl(this, 200, 200, kKnob, &knob);
  
  // Icon bitmaps
  IBitmap osc1 = pGraphics->LoadIBitmap(OSC1_ID, OSC1_FN, 1);
  IBitmap osc2 = pGraphics->LoadIBitmap(OSC2_ID, OSC2_FN, 1);
  IBitmap bqf1 = pGraphics->LoadIBitmap(BQF1_ID, BQF1_FN, 1);
  IBitmap bqf2 = pGraphics->LoadIBitmap(BQF2_ID, BQF2_FN, 1);
  IBitmap cho1 = pGraphics->LoadIBitmap(CHO1_ID, CHO1_FN, 1);
  IBitmap cho2 = pGraphics->LoadIBitmap(CHO2_ID, CHO2_FN, 1);
  IBitmap enva = pGraphics->LoadIBitmap(ENVA_ID, ENVA_FN, 1);
  IBitmap env1 = pGraphics->LoadIBitmap(ENV1_ID, ENV1_FN, 1);
  IBitmap env2 = pGraphics->LoadIBitmap(ENV2_ID, ENV2_FN, 1);
  IBitmap env3 = pGraphics->LoadIBitmap(ENV3_ID, ENV3_FN, 1);
  IBitmap fln1 = pGraphics->LoadIBitmap(FLN1_ID, FLN1_FN, 1);
  IBitmap fln2 = pGraphics->LoadIBitmap(FLN2_ID, FLN2_FN, 1);
  IBitmap fmf1 = pGraphics->LoadIBitmap(FMF1_ID, FMF1_FN, 1);
  IBitmap fmf2 = pGraphics->LoadIBitmap(FMF2_ID, FMF2_FN, 1);
  IBitmap lfo1 = pGraphics->LoadIBitmap(LFO1_ID, LFO1_FN, 1);
  IBitmap lfo2 = pGraphics->LoadIBitmap(LFO2_ID, LFO2_FN, 1);
  IBitmap lfo3 = pGraphics->LoadIBitmap(LFO3_ID, LFO3_FN, 1);
  IBitmap lfo4 = pGraphics->LoadIBitmap(LFO4_ID, LFO4_FN, 1);
  IBitmap spf1 = pGraphics->LoadIBitmap(SPF1_ID, SPF1_FN, 1);
  IBitmap spf2 = pGraphics->LoadIBitmap(SPF2_ID, SPF2_FN, 1);
  
  // Icon controls
  ISwitchControl* osc1Control = new ISwitchControl(this, 20, kViewLeftT + 15, kOsc1, &osc1);
  ISwitchControl* osc2Control = new ISwitchControl(this, 80, kViewLeftT + 15, kOsc2, &osc2);
  ISwitchControl* bqf1Control = new ISwitchControl(this, 140, kViewLeftT + 15, kBqf1, &bqf1);
  ISwitchControl* bqf2Control = new ISwitchControl(this, 200, kViewLeftT + 15, kBqf2, &bqf2);
  ISwitchControl* cho1Control = new ISwitchControl(this, 20, kViewLeftT + 65, kCho1, &cho1);
  ISwitchControl* cho2Control = new ISwitchControl(this, 80, kViewLeftT + 65, kCho2, &cho2);
  ISwitchControl* envaControl = new ISwitchControl(this, 140, kViewLeftT + 65, kEnva, &enva);
  ISwitchControl* env1Control = new ISwitchControl(this, 200, kViewLeftT + 65, kEnv1, &env1);
  ISwitchControl* env2Control = new ISwitchControl(this, 20, kViewLeftT + 115, kEnv2, &env2);
  ISwitchControl* env3Control = new ISwitchControl(this, 80, kViewLeftT + 115, kEnv3, &env3);
  ISwitchControl* fln1Control = new ISwitchControl(this, 140, kViewLeftT + 115, kFln1, &fln1);
  ISwitchControl* fln2Control = new ISwitchControl(this, 200, kViewLeftT + 115, kFln2, &fln2);
  ISwitchControl* fmf1Control = new ISwitchControl(this, 20, kViewLeftT + 165, kFmf1, &fmf1);
  ISwitchControl* fmf2Control = new ISwitchControl(this, 80, kViewLeftT + 165, kFmf2, &fmf2);
  ISwitchControl* lfo1Control = new ISwitchControl(this, 140, kViewLeftT + 165, kLfoo1, &lfo1);
  ISwitchControl* lfo2Control = new ISwitchControl(this, 200, kViewLeftT + 165, kLfoo2, &lfo2);
  ISwitchControl* lfo3Control = new ISwitchControl(this, 20, kViewLeftT + 215, kLfoo3, &lfo3);
  ISwitchControl* lfo4Control = new ISwitchControl(this, 80, kViewLeftT + 215, kLfoo4, &lfo4);
  ISwitchControl* spf1Control = new ISwitchControl(this, 140, kViewLeftT + 215, kSpf1, &spf1);
  ISwitchControl* spf2Control = new ISwitchControl(this, 200, kViewLeftT + 215, kSpf2, &spf2);
  
  pGraphics->AttachControl(osc1Control);
  pGraphics->AttachControl(osc2Control);
  pGraphics->AttachControl(bqf1Control);
  pGraphics->AttachControl(bqf2Control);
  pGraphics->AttachControl(cho1Control);
  pGraphics->AttachControl(cho2Control);
  pGraphics->AttachControl(envaControl);
  pGraphics->AttachControl(env1Control);
  pGraphics->AttachControl(env2Control);
  pGraphics->AttachControl(env3Control);
  pGraphics->AttachControl(fln1Control);
  pGraphics->AttachControl(fln2Control);
  pGraphics->AttachControl(fmf1Control);
  pGraphics->AttachControl(fmf2Control);
  pGraphics->AttachControl(lfo1Control);
  pGraphics->AttachControl(lfo2Control);
  pGraphics->AttachControl(lfo3Control);
  pGraphics->AttachControl(lfo4Control);
  pGraphics->AttachControl(spf1Control);
  pGraphics->AttachControl(spf2Control);
  
  model->loadGUIElements(pGraphics, this);

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
    case kOsc1:
      break;
    case kKnob:
//      std::cout << "Detune value: " << GetParam(kKnob)->Value() << std::endl;
      for (int i=0; i<MAX_VOICES+1; i++) {
        model->oscillatorGroup1[i]->changeDetuneAmt(GetParam(kKnob)->Value());
      }
      break;
    case kPan:
//      std::cout << "Pan value: " << GetParam(kPan)->Value() << std::endl;
      for (int i=0; i<MAX_VOICES+1; i++) {
        model->oscillatorGroup1[i]->changePanAmt(GetParam(kPan)->Value());
      }
    case kVolume:
//      std::cout << "Pan value: " << GetParam(kVolume)->Value() << std::endl;
      for (int i=0; i<MAX_VOICES+1; i++) {
        model->oscillatorGroup1[i]->changeVolume(GetParam(kVolume)->Value());
      }
      break;
      default:
      break;
  }
}

void AudioComponents::connectModulator(Modulator* modulator, Parameter* parameter) {
  parameter->addModulator(modulator);
}
