#ifndef __VEGA__
#define __VEGA__

#include "IPlug_include_in_plug_hdr.h"
#include "VoiceEngine.h"
#include "MIDIReceiver.h"

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
  void CreateParams();
  void CreateGraphics();
  void CreatePresets();
  void processVirtualKeyboard();
  IControl* mVirtualKeyboard;
  MIDIReceiver mMIDIReceiver;
  VoiceEngine mVoiceEngine;
};

#endif
