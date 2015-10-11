#include "Vega.h"
#include "IPlug_include_in_plug_src.h"
#include "IControl.h"
#include "resource.h"
#include "IKeyboardControl.h"

const int kNumPrograms = 0;

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
  mFilterCtlCutoff,
  mFilterCtlReso,
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
  mBendRange,
  mGlide,
  mPitchMod,
  kNumParams
};

const double parameterStep = 0.01;

typedef struct
{
  const char* name;
  int x;
  int y;
  const double defaultVal;
  const double minVal;
  const double maxVal;
} paramProperties;

paramProperties paramProps[kNumParams] = {
  { "Osc 1 Wave", 57, 104, 0.0, 0.0, 0.0 },
  { "Osc 1 Octave", 131, 104, 0.0, -4.0, 4.0 },
  { "Osc 1 Voices", 57, 120, 1.0, 1.0, 8.0 },
  { "Osc 1 Pitch", 131, 120, 0.0, -7.0, 7.0 },
  { "Osc 1 Invert", 244, 104, 0.0, 0.0, 1.0 },
  { "Osc 1 Retrig", 244, 120, 0.0, 0.0, 1.0 },
  { "Osc 1 Fine", 180, 106, 0.0, -1.0, 1.0 },
  { "Osc 1 Volume", 20, 149, 1.0, 0.0, 1.0 },
  { "Osc 1 Detune", 69, 149, 0.0, 0.0, 1.0 },
  { "Osc 1 Stereo", 118, 149, 0.0, -1.0, 1.0 },
  { "Osc 1 Phase", 167, 149, 0.0, 0.0, 360.0 },
  { "Osc 1 Pan", 216, 149, 0.0, -1.0, 1.0 },
  { "Osc 2 Wave", 57, 231, 0.0, 0.0, 0.0 },
  { "Osc 2 Octave", 131, 231, 0.0, -4.0, 4.0 },
  { "Osc 2 Voices", 57, 247, 1.0, 1.0, 8.0 },
  { "Osc 2 Pitch", 131, 247, 0.0, -7.0, 7.0 },
  { "Osc 2 Invert", 244, 231, 0.0, 0.0, 1.0 },
  { "Osc 2 Retrig", 244, 247, 0.0, 0.0, 1.0 },
  { "Osc 2 Fine", 180, 233, 0.0, -1.0, 1.0 },
  { "Osc 2 Volume", 20, 276, 1.0, 0.0, 1.0 },
  { "Osc 2 Detune", 69, 276, 0.0, 0.0, 1.0 },
  { "Osc 2 Stereo", 118, 276, 0.0, -1.0, 1.0 },
  { "Osc 2 Phase", 167, 276, 0.0, 0.0, 360.0 },
  { "Osc 2 Pan", 216, 276, 0.0, -1.0, 1.0 },
  { "Osc 3 Wave", 57, 358, 0.0, 0.0, 0.0 },
  { "Osc 3 Octave", 131, 358, 0.0, -4.0, 4.0 },
  { "Osc 3 Voices", 57, 374, 1.0, 1.0, 8.0 },
  { "Osc 3 Pitch", 131, 374, 0.0, -7.0, 7.0 },
  { "Osc 3 Invert", 244, 358, 0.0, 0.0, 1.0 },
  { "Osc 3 Retrig", 244, 374, 0.0, 0.0, 1.0 },
  { "Osc 3 Fine", 180, 360, 0.0, -1.0, 1.0 },
  { "Osc 3 Volume", 20, 403, 1.0, 0.0, 1.0 },
  { "Osc 3 Detune", 69, 403, 0.0, 0.0, 1.0 },
  { "Osc 3 Stereo", 118, 403, 0.0, -1.0, 1.0 },
  { "Osc 3 Phase", 167, 403, 0.0, 0.0, 360.0 },
  { "Osc 3 Pan", 216, 403, 0.0, -1.0, 1.0 },
  { "Filter Type", 332, 221, 0.0, 0.0, 0.0 },
  { "Filter Slope", 332, 237, 1.0, 1.0, 3.0 },
  { "Filter Cutoff", 375, 217, 0.99, 0.0, 0.99 },
  { "Filter Resonance", 424, 217, 0.0, 0.0, 0.99 },
  { "Filter Env Amount", 473, 217, 0.0, 0.0, 1.0 },
  { "Filter Control Cutoff", 285, 306, 0.99, 0.0, 0.99 },
  { "Filter Control Reso", 334, 306, 0.0, 0.0, 0.99 },
  { "Volume Env Attack", 350, 108, 0.01, 0.01, 10.0 },
  { "Volume Env Decay", 375, 108, 0.01, 0.01, 15.0 },
  { "Volume Env Sustain", 400, 108, 1.0, .001, 1.0 },
  { "Volume Env Release", 424, 108, 1.0, 0.01, 15.0 },
  { "Filter Env Attack", 400, 294, 0.01, 0.01, 10.0 },
  { "Filter Env Decay", 425, 294, 0.01, 0.01, 15.0 },
  { "Filter Env Sustain", 450, 294, 1.0, 0.001, 1.0 },
  { "Filter Env Release", 474, 294, 1.0, 0.01, 15.0 },
  { "LFO Waveform", 291, 417, 0.0, 0.0, 0.0 },
  { "LFO Amount", 326, 403, 1.0, 0.0, 1.0 },
  { "LFO Frequency", 375, 403, 6.0, 0.0, 50.0 },
  { "LFO Offset", 424, 403, 0.0, 0.0, 1.0 },
  { "LFO Gain", 473, 403, 0.0, 0.0, 12.0 },
  { "EQ High", 818, 111, 0.0, -6.0, 6.0 },
  { "EQ Mid", 818, 167, 0.0, -6.0, 6.0 },
  { "EQ Low", 818, 223, 0.0, -6.0, 6.0 },
  { "Out Vol", 811, 402, 0.5, 0.0, 1.0 },
  { "Bend Range", 13, 525, 0.0, -7.0, 7.0 },
  { "Glide", 9, 482, 0.0, 0.0, 1.0 },
  { "Pitch Mod", 52, 481, 0.0, -1.0, 1.0 }
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

  CreateGraphics();
  CreateParams();
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
    case mLFOWave:
      param->InitEnum(properties.name,
        Oscillator::OSCILLATOR_MODE_SAW,
        Oscillator::kNumOscillatorModes);
      // For VST3:
      param->SetDisplayText(0, properties.name);
      break;
    case mFilterType:
      param->InitEnum(properties.name,
        Filter::FILTER_MODE_LOWPASS,
        Filter::kNumFilterModes);
      param->SetDisplayText(0, properties.name);
      break;
      // Integer Parameters (Using double notation)
    case mOsc1Oct:
    case mOsc2Oct:
    case mOsc3Oct:
    case mOsc1Pitch:
    case mOsc2Pitch:
    case mOsc3Pitch:
    case mOsc1Phase:
    case mOsc2Phase:
    case mOsc3Phase:
    case mBendRange:
    case mOsc1Voices:
    case mOsc2Voices:
    case mOsc3Voices:
    case mFilterSlope:
      param->InitInt(properties.name,
        (int)properties.defaultVal,
        (int)properties.minVal,
        (int)properties.maxVal);
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
  GetParam(mFilterCtlCutoff)->SetShape(2);
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
  IBitmap whiteKeyImage = pGraphics->LoadIBitmap(PIANO_WHT_ID, PIANO_WHT_FN, 6);
  IBitmap blackKeyImage = pGraphics->LoadIBitmap(PIANO_BLK_ID, PIANO_BLK_FN);
  IBitmap miniKnobImage = pGraphics->LoadIBitmap(MINIKNOB_ID, MINIKNOB_FN, kKnobFrames);
  IBitmap waveImage = pGraphics->LoadIBitmap(WAVE_ID, WAVE_FN, 4);
  IBitmap slopeImage = pGraphics->LoadIBitmap(SLOPE_ID, SLOPE_FN, 3);
  IBitmap voicesImage = pGraphics->LoadIBitmap(VOICES_ID, VOICES_FN, 8);
  IBitmap octaveImage = pGraphics->LoadIBitmap(OCTAVE_ID, OCTAVE_FN, 9);
  IBitmap noteImage = pGraphics->LoadIBitmap(NOTE_ID, NOTE_FN, 15);
  IBitmap passImage = pGraphics->LoadIBitmap(PASS_ID, PASS_FN, 3);
  IBitmap sliderImage = pGraphics->LoadIBitmap(SLIDER_ID, SLIDER_FN, 1);
  IBitmap buttonGrnImage = pGraphics->LoadIBitmap(BUTTON_ID, BUTTON_FN, 2);
  IBitmap buttonAddImage = pGraphics->LoadIBitmap(ADD_ID, ADD_FN, 2);
  IBitmap wheelImage = pGraphics->LoadIBitmap(PITCHMOD_ID, PITCHMOD_FN, kKnobFrames);

  keyboardY = kHeight - 85;
  keyboardX = kWidth - 788;

  int keyCoordinates[12] = { 0, 17, 0, 49, 0, 0, 98, 0, 128, 0, 157, 0 };
  mVirtualKeyboard = new IKeyboardControl(this, keyboardX, keyboardY, virtualKeyboardMinimumNoteNumber,
    4, &whiteKeyImage, &blackKeyImage, keyCoordinates);
  pGraphics->AttachControl(mVirtualKeyboard);

  for (int i = 0; i < kNumParams; i++) {
    const paramProperties& properties = paramProps[i];
    IControl* control;
    IBitmap* graphic;
    switch (i) {
    case mOsc1Wave:
    case mOsc2Wave:
    case mOsc3Wave:
    case mLFOWave:
      graphic = &waveImage;
      control = new IKnobMultiControl(this, properties.x, properties.y, i, graphic);
      break;
    case mFilterType:
      graphic = &passImage;
      control = new IKnobMultiControl(this, properties.x, properties.y, i, graphic);
      break;
    case mFilterSlope:
      graphic = &slopeImage;
      control = new IKnobMultiControl(this, properties.x, properties.y, i, graphic);
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
      control = new IFaderControl(this, properties.x, properties.y, 73, i, graphic);
      break;
    case mOsc1Voices:
    case mOsc2Voices:
    case mOsc3Voices:
      graphic = &voicesImage;
      control = new IKnobMultiControl(this, properties.x, properties.y, i, graphic);
      break;
    case mOsc1Oct:
    case mOsc2Oct:
    case mOsc3Oct:
      graphic = &octaveImage;
      control = new IKnobMultiControl(this, properties.x, properties.y, i, graphic);
      break;
    case mOsc1Pitch:
    case mOsc2Pitch:
    case mOsc3Pitch:
    case mBendRange:
      graphic = &noteImage;
      control = new IKnobMultiControl(this, properties.x, properties.y, i, graphic);
      break;
    case mOsc1Fine:
    case mOsc2Fine:
    case mOsc3Fine:
    case mGlide:
      graphic = &miniKnobImage;
      control = new IKnobMultiControl(this, properties.x, properties.y, i, graphic);
      break;
    case mPitchMod:
      graphic = &wheelImage;
      control = new IKnobMultiControl(this, properties.x, properties.y, i, graphic);
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
