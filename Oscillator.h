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
  inline void setMuted(bool muted) { isMuted = muted; }
  double nextSample();
  Oscillator() :
    mOscillatorMode(OSCILLATOR_MODE_SINE),
    mFrequency(440.0),
    mPI(2 * acos(0.0)),
    mTwoPI(2 * mPI),
    isMuted(true),
    mPhase(0.0),
    mSampleRate(44100.0) {
     updateIncrement();
    };
  ~Oscillator();
private:
  OscillatorMode mOscillatorMode;
  const double mPI;
  const double mTwoPI;
  double mFrequency;
  double mPhase;
  double mSampleRate;
  double mPhaseIncrement;
  bool isMuted;
  void updateIncrement();
};

#endif

