#include "AudioComponents.h"
#include "IPlug_include_in_plug_src.h"
#include "IControl.h"
#include "resource.h"

const int kNumPrograms = 1;

enum EParams
{
  kGain = 0,
  kWaveform,
  kNumParams
};

enum ELayout
{
  kWidth = GUI_WIDTH,
  kHeight = GUI_HEIGHT,

  kGainX = 100,
  kGainY = 100,
  kKnobFrames = 60
};

/* CONSTRUCTOR */
AudioComponents::AudioComponents(IPlugInstanceInfo instanceInfo)
  :	IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo), mGain(1.)
{
  TRACE;
  
  GetParam(kWaveform)->InitInt("Waveform image multi", 0, 0, 5, "");
  
  /* --------------------------CREATE THE EFFECTS ---------------------------
   
                  Effects are created and initialized here.
   
   ----------------------------------------------------------------------------------*/
  
  openGLTestClass = new OpenGLTestClass(this, IRECT(10, kHeight - 100 - 10, 100 - 10, kHeight - 10));
  
  midiMsg = new IMidiMsg();
  cycleInterval = 176;
  count = 0;
  
  // Symphony
  symphony = new Symphony(1);
  
  // Oscillators
  oscillatorGroup = new OscillatorGroup(16, Bb_2, WaveType::SAW);
  
  // Distortion
  distortionLeft = new Distortion(1.0);
  distortionRight = new Distortion(1.0);
  
  // Overdrive
  softClipLeft = new SymmetricalSoftClip();
  softClipRight = new SymmetricalSoftClip();
  
  // Biquad Filter
  filterLeft = new Filter(LPF, 0.0, 5000, SAMPLE_RATE, 2);
  filterRight = new Filter(LPF, 0.0, 5000, SAMPLE_RATE, 2);
  
  // Formant Filter
  formantFilterLeft = new FormantFilter(Vowel::O);
  formantFilterRight = new FormantFilter(Vowel::O);
  
  // Delay 1
  delayLeft = new SampleDelay(319, 0.90);
  delayRight = new SampleDelay(397, 0.90);
  
  // Delay 2
  blockDelayLeft = new BlockDelay(44100/30, 512, 0.10);
  blockDelayRight = new BlockDelay(44100/31, 512, 0.10);
  
  // Delay 3
  blockDelayLeft2 = new BlockDelay(44100/4, 512, 0.80);
  blockDelayRight2 = new BlockDelay(44100/8, 512, 0.80);
  
  // Chorus
  chorusLeft = new Chorus(512, 6, 800, 0.3, 0.10);
  chorusRight = new Chorus(512, 6, 800, 0.3, 0.10);
  
  // Flanger
  flangerLeft = new Flanger(75, 0.5, 0.3, 0.85, WaveType::SINE);
  flangerRight = new Flanger(75, 0.5, 0.3, 0.85, WaveType::SINE);
  
  /* --------------------------CREATE THE PROCESSING CHAINS ---------------------------   
   
              Effects must be added to the chain in order to affect the sound.
              Each effect will be called in the order it was added to the chain.
   
   ----------------------------------------------------------------------------------*/
  
  // Sample Processing Chains
  processingChainLeft = new SampleEffectProcessingChain();
  processingChainLeft->addEffect(formantFilterLeft); // Add formant filter to chain

  processingChainRight = new SampleEffectProcessingChain();
  processingChainRight->addEffect(formantFilterRight); // Add formant filter to chain

  
  // Block Processing Chains
  blockProcessingChainLeft = new BlockEffectProcessingChain();
  blockProcessingChainLeft->addEffect(blockDelayLeft2); // Add block delay to chain
  blockProcessingChainLeft->addEffect(blockDelayLeft); // Add block delay to chain
  
  blockProcessingChainRight = new BlockEffectProcessingChain();
  blockProcessingChainRight->addEffect(blockDelayRight2); // Add block delay to chain
  blockProcessingChainRight->addEffect(blockDelayRight); // Add block delay to chain

  //arguments are: name, defaultVal, minVal, maxVal, step, label
  GetParam(kGain)->InitDouble("Gain", 50., 0., 100.0, 0.01, "%");
  GetParam(kGain)->SetShape(2.);
  
  

  IGraphics* pGraphics = MakeGraphics(this, kWidth, kHeight);
  pGraphics->AttachPanelBackground(&COLOR_RED);

  IBitmap knob = pGraphics->LoadIBitmap(KNOB_ID, KNOB_FN, kKnobFrames);
  
  IBitmap bitmap = pGraphics->LoadIBitmap(ISWITCHCONTROL_6_ID, ISWITCHCONTROL_6_FN, 6, false);
  
  pGraphics->AttachControl(new ISwitchControl(this, 216, 72, kWaveform, &bitmap));

  pGraphics->AttachControl(new IKnobMultiControl(this, kGainX, kGainY, kGain, &knob));

  pGraphics->AttachControl(openGLTestClass);
  
  AttachGraphics(pGraphics);

  //MakePreset("preset 1", ... );
  MakeDefaultPreset((char *) "-", kNumPrograms);
}

AudioComponents::~AudioComponents() {}

void AudioComponents::ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames)
{
  
//  if (count++ == cycleInterval) {
//    if (flag) {
////      midiMsg->MakeNoteOnMsg(47, 127, 0);
////      ProcessMidiMsg(midiMsg);
//      flag = !flag;
//      symphony->changeWaveType(WaveType::SAW);
//    } else {
////      midiMsg->MakeNoteOffMsg(47, 0);
////      ProcessMidiMsg(midiMsg);
//      flag = !flag;
//      symphony->changeWaveType(WaveType::SINE);
//    }
//    count = 0;
//  }
  // Mutex is already locked for us.
//
//  double* in1 = inputs[0]; // Comment this line out if plugin is a MIDI instrument; otherwise plugin will crash!
//  double* in2 = inputs[1]; // Comment this line out if plugin is a MIDI instrument; otherwise plugin will crash!
  double* out1 = outputs[0];
  double* out2 = outputs[1];
    
  double *samplesLeft = symphony->getSamplesLeft(nFrames);
  double *samplesRight = symphony->getSamplesRight(nFrames);
  
  // Perform all sample processing here
  for (int i=0; i<nFrames; i++) {
    out1[i] = samplesLeft[i];
    out2[i] = samplesRight[i];
  }
  
  // Perform all block processing here
//  blockProcessingChainLeft->process(out1, out1, nFrames);
//  blockProcessingChainRight->process(out2, out2, nFrames);
  
  delete samplesLeft;
  delete samplesRight;

//  for (int s = 0; s < nFrames; ++s, ++in1, ++in2, ++out1, ++out2)
//  {
//    *out1 = *in1 * mGain;
//    *out2 = *in2 * mGain;
//  }
}

/*
 *  Processes all midi messages
 */
void AudioComponents::ProcessMidiMsg(IMidiMsg *pMsg) {
  IMidiMsg::EStatusMsg status = pMsg->StatusMsg();
  
  // Note on message received
  if(status == IMidiMsg::kNoteOn) {
    
    // MIDI note number
    int noteNumber = pMsg->NoteNumber();
    
    // Convert note number to frequency (later, look up value in a table)
    double noteFrequency = 440.0 * pow(2.0, (noteNumber - 69.0) / 12.0);
    
    // Assign note to a new voice
    symphony->activateVoice(noteFrequency, noteNumber);
    
    std::cout << "Note on message received" << std::endl;
    
    // Note off message received
  } else if (status == IMidiMsg::kNoteOff) {
    
    // MIDI note number
    int noteNumber = pMsg->NoteNumber();
    
    // Deactivate voice
    symphony->deactivateVoice(noteNumber);
    std::cout << "Note off message received" << std::endl;
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
    case kGain:
      mGain = GetParam(kGain)->Value() / 100.;
      break;
    case kWaveform:
      int value = (int)GetParam(kWaveform)->Value();
      if (value == 0) {
        symphony->changeWaveType(WaveType::SAW);
      } else if (value == 1) {
        symphony->changeWaveType(WaveType::SINE);
      } else if (value == 2) {
        symphony->changeWaveType(WaveType::SQUARE);
      } else if (value == 3) {
        symphony->changeWaveType(WaveType::TRIANGLE);
      } else if (value == 4) {
        symphony->changeWaveType(WaveType::PULSE);
      } else if (value == 5) {
        symphony->changeWaveType(WaveType::NOISE);
      } else {
        
      }
      
//      std::cout << "waveform changed, value: " << GetParam(kWaveform)->Value() << std::endl;
      break;

//    default:
//      break;
  }
}
