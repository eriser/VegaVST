#include "Oscillator.h"

double Oscillator::mSampleRate = 44100.0;

Oscillator::~Oscillator() {}

void Oscillator::setMode(OscillatorMode mode) {
  mOscillatorMode = mode;
}

void Oscillator::setFrequency(double frequency) {
  mFrequency = frequency;
  updateIncrement();
}

void Oscillator::setSampleRate(double sampleRate) {
  mSampleRate = sampleRate;
  updateIncrement();
}

void Oscillator::updateIncrement() {
  mPhaseIncrement = mFrequency * 2 * mPI / mSampleRate;
}

double Oscillator::nextSample() {
  double value = 0.0;
  if (isMuted) return value;

  switch (mOscillatorMode) {
  case OSCILLATOR_MODE_SINE:
    value = sin(mPhase);
    break;
  case OSCILLATOR_MODE_SAW:
    value = 1.0 - (2.0 * mPhase / mTwoPI);
    break;
  case OSCILLATOR_MODE_SQUARE:
    if (mPhase <= mPI) {
      value = 1.0;
    } else {
      value = -1.0;
    }
    break;
  case OSCILLATOR_MODE_TRIANGLE:
    value = -1.0 + (2.0 * mPhase / mTwoPI);
    value = 2.0 * (fabs(value) - 0.5);
    break;
  }
  mPhase += mPhaseIncrement;
  while (mPhase >= mTwoPI) {
    mPhase -= mTwoPI;
  }
  return value;
}


