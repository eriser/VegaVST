#pragma once
#include "Oscillator.h"
#include "EnvelopeGenerator.h"
#include "Filter.h"

#define MAX_OSC 3

class Voice
{
private:
  Oscillator mOsc[MAX_OSC];
  EnvelopeGenerator mVolumeEnvelope, mFilterEnvelope;
  Filter mFilter;
  int mNoteNumber;
  int mVelocity;
  static int mActiveOscs;
  double mFilterEnvelopeAmount, mFilterCutoff, mFilterReso;
  double mOscVol[MAX_OSC];
  double mOscPitch[MAX_OSC];
  double mOscDetune[MAX_OSC];
  double mOscPhase[MAX_OSC];
  double mOscPan[MAX_OSC];
  double mLFOAmount, mLFOFreq, mLFOOffset, mLFOGain, mLFOValue;
  bool isActive;
public:
  friend class VoiceEngine;
  ~Voice();
  Voice()
    : mNoteNumber(-1),
    mVelocity(0),
    mFilterEnvelopeAmount(0.0),
    mFilterCutoff(0.0),
    mFilterReso(0.0),
    mLFOAmount(0.0),
    mLFOFreq(0.0),
    mLFOOffset(0.0),
    mLFOGain(0.0),
    mLFOValue(0.0),
    isActive(false) {
      // Set myself free everytime my volume envelope has fully faded out of RELEASE stage:
      mVolumeEnvelope.finishedEnvelopeCycle.Connect(this, &Voice::setFree);
    };

  inline void setActiveOscs(int activeOscs) { mActiveOscs = activeOscs; }
  inline void setFilterEnvelopeAmount(double amount) { mFilterEnvelopeAmount = amount; }
  inline void setOscillatorPitch(int osc, double amount) { mOscPitch[osc] = amount; }
  inline void setOscillatorDetune(int osc, double amount) { mOscDetune[osc] = amount; }
  inline void setOscillatorVolume(int osc, double amount) { mOscVol[osc] = amount; }
  inline void setOscillatorPhase(int osc, double amount) { mOscPhase[osc] = amount; }
  inline void setOscillatorPan(int osc, double amount) { mOscPan[osc] = amount; }
  inline void setOscillatorVol(int osc, double amount) { mOscPan[osc] = amount; }
  inline void setLFOAmount(double amount) { mLFOAmount = amount; }
  inline void setLFOOffset(double amount) { mLFOOffset = amount; }
  inline void setLFOFreq(double amount) { mLFOFreq = amount; }
  inline void setLFOGain(double amount) { mLFOGain = amount; }
  inline void setLFOValue(double amount) { mLFOValue = amount; }
  inline void setNoteNumber(int noteNumber) {
    mNoteNumber = noteNumber;
    double frequency = 440.0 * pow(2.0, (mNoteNumber - 69.0) / 12.0);
    for (int i = 0; i < MAX_OSC; i++) {
      mOsc[i].setFrequency(frequency);
    }
  }

  void reset();
  double nextSample();
  void setFree();
};

