#ifndef __VEGA__
#define __VEGA__

#include "IPlug_include_in_plug_hdr.h"
#include "Oscillator.h"
#include "MIDIReceiver.h"
#include "EnvelopeGenerator.h"
#include "Filter.h"

class Vega : public IPlug
{
public:
  Vega(IPlugInstanceInfo instanceInfo);
  ~Vega();

  inline int GetNumKeys() const { return mMIDIReceiver.getNumKeys(); };
  inline bool GetKeyStatus(int key) const { return mMIDIReceiver.getKeyStatus(key); };
  static const int virtualKeyboardMinimumNoteNumber = 48;
  int lastVirtualKeyboardNoteNumber;

  void Reset();
  void OnParamChange(int paramIdx);
  void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);
  void ProcessMidiMsg(IMidiMsg* pMsg);

private:
  double mFrequency;
  double filterEnvelopeAmount;
  double lfoFilterModAmount;
  void CreateParams();
  void CreateGraphics();
  void CreatePresets();
  void processVirtualKeyboard();
  IControl* mVirtualKeyboard;
  Oscillator mOscillator;
  Oscillator mLFO;
  MIDIReceiver mMIDIReceiver;
  EnvelopeGenerator mEnvelopeGenerator;
  EnvelopeGenerator mFilterEnvelopeGenerator;
  Filter mFilter;

  inline void onNoteOn(const int noteNumber, const int velocity) {
    mEnvelopeGenerator.enterStage(EnvelopeGenerator::ENVELOPE_STAGE_ATTACK);
    mFilterEnvelopeGenerator.enterStage(EnvelopeGenerator::ENVELOPE_STAGE_ATTACK);
  };
  inline void onNoteOff(const int noteNumber, const int velocity) {
    mEnvelopeGenerator.enterStage(EnvelopeGenerator::ENVELOPE_STAGE_RELEASE);
    mFilterEnvelopeGenerator.enterStage(EnvelopeGenerator::ENVELOPE_STAGE_RELEASE);
  };
  inline void onBeganEnvelopeCycle() { mOscillator.setMuted(false); }
  inline void onFinishedEnvelopeCycle() { mOscillator.setMuted(true); }
};

#endif
