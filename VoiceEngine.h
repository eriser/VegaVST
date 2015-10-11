#pragma once
#include "Voice.h"

class VoiceEngine
{
private:
  static const int NumberOfVoices = 64;
  Voice voices[NumberOfVoices];
  Oscillator mLFO;
  Voice* findFreeVoice();
public:
  VoiceEngine();
  ~VoiceEngine();
  void onNoteOn(int noteNumber, int velocity);
  void onNoteOff(int noteNumber, int velocity);
  double nextSample();
  void setSampleRate(double sampleRate);
};

