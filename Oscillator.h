#pragma once
#ifndef __OSCILLATOR__
#define __OSCILLATOR__

#include <math.h>

class Oscillator
{
public:
  enum OscillatorMode {
    OSCILLATOR_MODE_SINE,
    OSCILLATOR_MODE_SAW,
    OSCILLATOR_MODE_SQUARE,
    OSCILLATOR_MODE_TRIANGLE,
    kNumOscillatorModes
  };
  void setMode(OscillatorMode mode);
  void setFrequency(double frequency);
  void setSampleRate(double sampleRate);
  inline void reset() { mPhase = 0.0; }
  double nextSample();
  Oscillator() :
    mOscillatorMode(OSCILLATOR_MODE_SINE),
    mFrequency(440.0),
    mPI(2 * acos(0.0)),
    mTwoPI(2 * mPI),
    mPhase(0.0) {
     updateIncrement();
    };
  ~Oscillator();
private:
  OscillatorMode mOscillatorMode;
  const double mPI;
  const double mTwoPI;
  double mFrequency;
  double mPhase;
  static double mSampleRate;
  double mPhaseIncrement;
  void updateIncrement();
};

#endif

