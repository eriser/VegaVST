#include "Vega.h"
#include "IPlug_include_in_plug_src.h"
#include "IControl.h"
#include "resource.h"
#include "IKeyboardControl.h"

const int kNumPrograms = 5;

enum EParams
{
  mOsc1Wave = 0,
  mOsc1Oct,
  mOsc1Voices,
  mOsc1Pitch,
  mOsc1Invert,
  mOsc1Retrig,
  mOsc1Fine,
  mOsc1Volume,
  mOsc1Detune,
  mOsc1Stereo,
  mOsc1Phase,
  mOsc1Pan,
  mOsc2Wave,
  mOsc2Oct,
  mOsc2Voices,
  mOsc2Pitch,
  mOsc2Invert,
  mOsc2Retrig,
  mOsc2Fine,
  mOsc2Volume,
  mOsc2Detune,
  mOsc2Stereo,
  mOsc2Phase,
  mOsc2Pan,
  mOsc3Wave,
  mOsc3Oct,
  mOsc3Voices,
  mOsc3Pitch,
  mOsc3Invert,
  mOsc3Retrig,
  mOsc3Fine,
  mOsc3Volume,
  mOsc3Detune,
  mOsc3Stereo,
  mOsc3Phase,
  mOsc3Pan,
  mFilterType,
  mFilterSlope,
  mFilterCutoff,
  mFilterReso,
  mFilterAmount,
  mVolAttack,
  mVolDecay,
  mVolSustain,
  mVolRelease,
  mFilterAttack,
  mFilterDecay,
  mFilterSustain,
  mFilterRelease,
  mLFOWave,
  mLFOAmount,
  mLFOFrequency,
  mLFOOffset,
  mLFOGain,
  mEQHigh,
  mEQMid,
  mEQLow,
  mVolume,
  kNumParams
};

const double parameterStep = 0.01;

typedef struct
{
  const char* name;
  const int x;
  const int y;
  const double defaultVal;
  const double minVal;
  const double maxVal;
} paramProperties;

const paramProperties paramProps[kNumParams] = {
  { "Osc 1 Wave", 30, 75, 0., 0., 0. },
  { "Osc 1 Octave", 30, 75, 0., 0., 0. },
  { "Osc 1 Voices", 30, 75, 0., 0., 0. },
  { "Osc 1 Pitch", 69, 61, 0., 0., 0. },
  { "Osc 1 Invert", 30, 75, 0., 0., 0. },
  { "Osc 1 Retrig", 30, 75, 0., 0., 0. },
  { "Osc 1 Fine", 30, 75, 0., -1., 1. },
  { "Osc 1 Volume", 30, 75, 0., 0., 1. },
  { "Osc 1 Detune", 30, 75, 0., 0., 1. },
  { "Osc 1 Stereo", 30, 75, 0., 0., 1. },
  { "Osc 1 Phase", 30, 75, 0., 0., 1. },
  { "Osc 1 Pan", 30, 75, 0., -1., 1. },
  { "Osc 2 Wave", 30, 75, 0., 0., 0. },
  { "Osc 2 Octave", 30, 75, 0., 0., 0. },
  { "Osc 2 Voices", 30, 75, 0., 0., 0. },
  { "Osc 2 Pitch", 69, 61, 0., 0., 0. },
  { "Osc 2 Invert", 30, 75, 0., 0., 0. },
  { "Osc 2 Retrig", 30, 75, 0., 0., 0. },
  { "Osc 2 Fine", 30, 75, 0., -1., 1. },
  { "Osc 2 Volume", 30, 75, 0., 0., 1. },
  { "Osc 2 Detune", 30, 75, 0., 0., 1. },
  { "Osc 2 Stereo", 30, 75, 0., 0., 1. },
  { "Osc 2 Phase", 30, 75, 0., 0., 1. },
  { "Osc 2 Pan", 30, 75, 0., -1., 1. },
  { "Osc 3 Wave", 30, 75, 0., 0., 0. },
  { "Osc 3 Octave", 30, 75, 0., 0., 0. },
  { "Osc 3 Voices", 30, 75, 0., 0., 0. },
  { "Osc 3 Pitch", 69, 61, 0., 0., 0. },
  { "Osc 3 Invert", 30, 75, 0., 0., 0. },
  { "Osc 3 Retrig", 30, 75, 0., 0., 0. },
  { "Osc 3 Fine", 30, 75, 0., -1., 1. },
  { "Osc 3 Volume", 30, 75, 0., 0., 1. },
  { "Osc 3 Detune", 30, 75, 0., 0., 1. },
  { "Osc 3 Stereo", 30, 75, 0., 0., 1. },
  { "Osc 3 Phase", 30, 75, 0., 0., 1. },
  { "Osc 3 Pan", 30, 75, 0., -1., 1. },
  { "Filter Type", 30, 188, 0., 0., 0. },
  { "Filter Slope", 30, 188, 0., 0., 0. },
  { "Filter Cutoff", 69, 174, 0.99, 0.0, 0.99 },
  { "Filter Resonance", 124, 174, 0.0, 0.0, 1.0 },
  { "Filter Env Amount", 234, 174, 0.0, -1.0, 1.0 },
  { "Volume Env Attack", 323, 61, 0.01, 0.01, 10.0 },
  { "Volume Env Decay", 378, 61, 0.5, 0.01, 15.0 },
  { "Volume Env Sustain", 433, 61, 0.1, 0.001, 1.0 },
  { "Volume Env Release", 488, 61, 1.0, 0.01, 15.0 },
  { "Filter Env Attack", 323, 174, 0.01, 0.01, 10.0 },
  { "Filter Env Decay", 378, 174, 0.5, 0.01, 15.0 },
  { "Filter Env Sustain", 433, 174, 0.1, 0.001, 1.0 },
  { "Filter Env Release", 488, 174, 1.0, 0.01, 15.0 },
  { "LFO Waveform", 30, 298, 0., 0., 0. },
  { "LFO Amount", 179, 174, 0.0, 0.0, 1.0 },
  { "LFO Frequency", 69, 284, 6.0, 0.01, 30.0 },
  { "LFO Offset", 69, 284, 6.0, 0.01, 30.0 },
  { "LFO Gain", 69, 284, 6.0, 0.01, 30.0 },
  { "EQ High", 323, 174, 1.0, 0.0, 2.0 },
  { "EQ Mid", 378, 174, 1.0, 0.0, 2.0 },
  { "EQ Low", 433, 174, 1.0, 0.0, 2.0 },
  { "Out Vol", 433, 174, 1.0, 0.0, 1.0 }
};

enum ELayout
{
  kWidth = GUI_WIDTH,
  kHeight = GUI_HEIGHT,
  kKeyboardX = 0,
  kKeyboardY = 0,
  kKnobFrames = 100
};

Vega::Vega(IPlugInstanceInfo instanceInfo)
  :	IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo), mFrequency(1.),
  lastVirtualKeyboardNoteNumber(virtualKeyboardMinimumNoteNumber - 1),
  filterEnvelopeAmount(0.0), lfoFilterModAmount(0.1)
{
  TRACE;

  CreateParams();
  CreateGraphics();
  CreatePresets();

  mMIDIReceiver.noteOn.Connect(this, &Vega::onNoteOn);
  mMIDIReceiver.noteOff.Connect(this, &Vega::onNoteOff);
  mEnvelopeGenerator.beganEnvelopeCycle.Connect(this, &Vega::onBeganEnvelopeCycle);
  mEnvelopeGenerator.finishedEnvelopeCycle.Connect(this, &Vega::onFinishedEnvelopeCycle);
}

Vega::~Vega() {}

void Vega::processVirtualKeyboard() {
  IKeyboardControl* virtualKeyboard = (IKeyboardControl*) mVirtualKeyboard;
  int virtualKeyboardNoteNumber = virtualKeyboard->GetKey() + virtualKeyboardMinimumNoteNumber;

  if (lastVirtualKeyboardNoteNumber >= virtualKeyboardMinimumNoteNumber
    && virtualKeyboardNoteNumber != lastVirtualKeyboardNoteNumber) {
    IMidiMsg midiMessage;
    midiMessage.MakeNoteOffMsg(lastVirtualKeyboardNoteNumber, 0);
    mMIDIReceiver.onMessageReceived(&midiMessage);
  }

  if (virtualKeyboardNoteNumber >= virtualKeyboardMinimumNoteNumber
    && virtualKeyboardNoteNumber != lastVirtualKeyboardNoteNumber) {
    IMidiMsg midiMessage;
    midiMessage.MakeNoteOnMsg(virtualKeyboardNoteNumber, virtualKeyboard->GetVelocity(), 0);
    mMIDIReceiver.onMessageReceived(&midiMessage);
  }

  lastVirtualKeyboardNoteNumber = virtualKeyboardNoteNumber;
}

void Vega::ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames)
{
  // Mutex is already locked for us.

  double *leftOutput = outputs[0];
  double *rightOutput = outputs[1];

  processVirtualKeyboard();
  
  // Copy left buffer into right buffer:
  for (int s = 0; s < nFrames; ++s) {
    mMIDIReceiver.advance();
    int velocity = mMIDIReceiver.getLastVelocity();
    double lfoFilterModulation = mLFO.nextSample() * lfoFilterModAmount;
    mOscillator.setFrequency(mMIDIReceiver.getLastFrequency());
    mFilter.setCutoffMod((mFilterEnvelopeGenerator.nextSample() * filterEnvelopeAmount) + lfoFilterModulation);
    leftOutput[s] = rightOutput[s] = mOscillator.nextSample() * velocity / 127.0;
    mFilter.process(mOscillator.nextSample() * mEnvelopeGenerator.nextSample() * velocity / 127.0);
  }
  mMIDIReceiver.Flush(nFrames);
}

void Vega::CreateParams() {
  for (int i = 0; i < kNumParams; i++) {
    IParam* param = GetParam(i);
    const paramProperties& properties = paramProps[i];
    switch (i) {
      // Enum Parameters:
    case mOsc1Wave:
    case mOsc2Wave:
    case mOsc3Wave:
      param->InitEnum(properties.name,
        Oscillator::OSCILLATOR_MODE_SAW,
        Oscillator::kNumOscillatorModes);
      // For VST3:
      param->SetDisplayText(0, properties.name);
      break;
    case mLFOWave:
      param->InitEnum(properties.name,
        Oscillator::OSCILLATOR_MODE_TRIANGLE,
        Oscillator::kNumOscillatorModes);
      // For VST3:
      param->SetDisplayText(0, properties.name);
      break;
    case mFilterType:
      param->InitEnum(properties.name,
        Filter::FILTER_MODE_LOWPASS,
        Filter::kNumFilterModes);
      break;
      // Double Parameters:
    default:
      param->InitDouble(properties.name,
        properties.defaultVal,
        properties.minVal,
        properties.maxVal,
        parameterStep);
      break;
    }
  }
  GetParam(mVolAttack)->SetShape(3);
  GetParam(mVolDecay)->SetShape(3);
  GetParam(mVolSustain)->SetShape(2);
  GetParam(mVolRelease)->SetShape(3);
  GetParam(mFilterCutoff)->SetShape(2);
  GetParam(mFilterAttack)->SetShape(3);
  GetParam(mFilterDecay)->SetShape(3);
  GetParam(mFilterSustain)->SetShape(2);
  GetParam(mFilterRelease)->SetShape(3);

  for (int i = 0; i < kNumParams; i++) {
    OnParamChange(i);
  }
}

void Vega::CreateGraphics() {
  int keyboardX, keyboardY;

  IGraphics* pGraphics = MakeGraphics(this, kWidth, kHeight);
  pGraphics->AttachBackground(BACKGROUND_ID, BACKGROUND_FN);

  IBitmap knobImage = pGraphics->LoadIBitmap(KNOB_ID, KNOB_FN, kKnobFrames);
  IBitmap miniKnobImage = pGraphics->LoadIBitmap(MINIKNOB_ID, MINIKNOB_FN, kKnobFrames);
  IBitmap waveImage = pGraphics->LoadIBitmap(WAVE_ID, WAVE_FN, 4);
  IBitmap slopeImage = pGraphics->LoadIBitmap(SLOPE_ID, SLOPE_FN, 3);
  IBitmap voicesImage = pGraphics->LoadIBitmap(VOICES_ID, VOICES_FN, 8);
  IBitmap octaveImage = pGraphics->LoadIBitmap(OCTAVE_ID, OCTAVE_FN, 7);
  IBitmap noteImage = pGraphics->LoadIBitmap(NOTE_ID, NOTE_FN, 15);
  IBitmap whiteKeyImage = pGraphics->LoadIBitmap(PIANO_WHT_ID, PIANO_WHT_FN, 6);
  IBitmap blackKeyImage = pGraphics->LoadIBitmap(PIANO_BLK_ID, PIANO_BLK_FN);
  IBitmap passImage = pGraphics->LoadIBitmap(PASS_ID, PASS_FN, 3);
  IBitmap sliderImage = pGraphics->LoadIBitmap(SLIDER_ID, SLIDER_FN, 1);
  IBitmap buttonGrnImage = pGraphics->LoadIBitmap(BUTTON_ID, BUTTON_FN, 1);
  IBitmap buttonAddImage = pGraphics->LoadIBitmap(ADD_ID, ADD_FN, 1);

  keyboardY = kHeight - 85;
  keyboardX = kWidth - 800;

  int keyCoordinates[12] = { 0, 7, 12, 20, 24, 36, 43, 48, 56, 60, 69, 72 };
  mVirtualKeyboard = new IKeyboardControl(this, keyboardX, keyboardY, virtualKeyboardMinimumNoteNumber,
    5, &whiteKeyImage, &blackKeyImage, keyCoordinates);
  pGraphics->AttachControl(mVirtualKeyboard);

  for (int i = 0; i < kNumParams; i++) {
    const paramProperties& properties = paramProps[i];
    IControl* control;
    IBitmap* graphic;
    switch (i) {
      // Switches:
    case mOsc1Wave:
    case mOsc2Wave:
    case mOsc3Wave:
    case mLFOWave:
      graphic = &waveImage;
      control = new ISwitchControl(this, properties.x, properties.y, i, graphic);
      break;
    case mFilterType:
      graphic = &passImage;
      control = new ISwitchControl(this, properties.x, properties.y, i, graphic);
      break;
    case mFilterSlope:
      graphic = &slopeImage;
      control = new ISwitchControl(this, properties.x, properties.y, i, graphic);
      break;
    case mOsc1Invert:
    case mOsc1Retrig:  
    case mOsc2Invert:
    case mOsc2Retrig:
    case mOsc3Invert:
    case mOsc3Retrig:
      graphic = &buttonGrnImage;    
      control = new ISwitchControl(this, properties.x, properties.y, i, graphic);
      break;
    case mVolAttack:
    case mVolDecay:
    case mVolSustain:
    case mVolRelease:
    case mFilterAttack:
    case mFilterDecay:
    case mFilterSustain:
    case mFilterRelease:
      graphic = &sliderImage;
      control = new IFaderControl(this, properties.x, properties.y, 50, i, graphic);
      break;
    case mOsc1Voices:
    case mOsc2Voices:
    case mOsc3Voices:
      graphic = &voicesImage;
      control = new ISwitchControl(this, properties.x, properties.y, i, graphic);
      break;
    case mOsc1Oct:
    case mOsc2Oct:
    case mOsc3Oct:
      graphic = &octaveImage;
      control = new ISwitchControl(this, properties.x, properties.y, i, graphic);
      break;
    case mOsc1Pitch:
    case mOsc2Pitch:
    case mOsc3Pitch:
      graphic = &noteImage;
      control = new ISwitchControl(this, properties.x, properties.y, i, graphic);
      break;
    case mOsc1Fine:
    case mOsc2Fine:
    case mOsc3Fine:
      graphic = &miniKnobImage;
      control = new IKnobMultiControl(this, properties.x, properties.y, i, graphic);
      break;
    case mVolume:
      graphic = &waveImage;
      control = new ISwitchControl(this, properties.x, properties.y, i, graphic);
      break;
    default:
      graphic = &knobImage;
      control = new IKnobMultiControl(this, properties.x, properties.y, i, graphic);
      break;
    }
    pGraphics->AttachControl(control);
  }

  AttachGraphics(pGraphics);
}

void Vega::CreatePresets() {
  MakePreset("clean", 440.0, 0);
}

void Vega::Reset()
{
  TRACE;
  IMutexLock lock(this);
  mOscillator.setSampleRate(GetSampleRate());
  mFilterEnvelopeGenerator.setSampleRate(GetSampleRate());
  mEnvelopeGenerator.setSampleRate(GetSampleRate());
  mLFO.setSampleRate(GetSampleRate());
}

void Vega::OnParamChange(int paramIdx)
{
  IMutexLock lock(this);
  int stage = 4;

  switch (paramIdx)
  {
    case mOsc1Wave:
      mOscillator.setMode(static_cast<Oscillator::OscillatorMode>(GetParam(mOsc1Wave)->Int()));
      break;
    case mVolAttack:
      mEnvelopeGenerator.setStageValue(EnvelopeGenerator::ENVELOPE_STAGE_ATTACK, GetParam(paramIdx)->Value());
      break;
    case mVolDecay:
      mEnvelopeGenerator.setStageValue(EnvelopeGenerator::ENVELOPE_STAGE_DECAY, GetParam(paramIdx)->Value());
      break;
    case mVolSustain:
      mEnvelopeGenerator.setStageValue(EnvelopeGenerator::ENVELOPE_STAGE_SUSTAIN, GetParam(paramIdx)->Value());
      break;
    case mVolRelease:
      mEnvelopeGenerator.setStageValue(EnvelopeGenerator::ENVELOPE_STAGE_RELEASE, GetParam(paramIdx)->Value());
      break;
    case mFilterCutoff:
      mFilter.setCutoff(GetParam(paramIdx)->Value());
      break;
    case mFilterReso:
      mFilter.setResonance(GetParam(paramIdx)->Value());
      break;
    case mFilterType:
      mFilter.setFilterMode(static_cast<Filter::FilterMode>(GetParam(paramIdx)->Int()));
      break;
    case mFilterAttack:
      mFilterEnvelopeGenerator.setStageValue(EnvelopeGenerator::ENVELOPE_STAGE_ATTACK, GetParam(paramIdx)->Value());
      break;
    case mFilterDecay:
      mFilterEnvelopeGenerator.setStageValue(EnvelopeGenerator::ENVELOPE_STAGE_DECAY, GetParam(paramIdx)->Value());
      break;
    case mFilterSustain:
      mFilterEnvelopeGenerator.setStageValue(EnvelopeGenerator::ENVELOPE_STAGE_SUSTAIN, GetParam(paramIdx)->Value());
      break;
    case mFilterRelease:
      mFilterEnvelopeGenerator.setStageValue(EnvelopeGenerator::ENVELOPE_STAGE_RELEASE, GetParam(paramIdx)->Value());
      break;
    case mFilterAmount:
      filterEnvelopeAmount = GetParam(paramIdx)->Value();
      break;
    default:
      break;
  }
}

void Vega::ProcessMidiMsg(IMidiMsg* pMsg) {
  mMIDIReceiver.onMessageReceived(pMsg);
  mVirtualKeyboard->SetDirty();
}
