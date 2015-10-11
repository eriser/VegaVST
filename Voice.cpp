#include "Voice.h"

int Voice::mActiveOscs = 1;

Voice::~Voice() {}

void Voice::reset() {
  mNoteNumber = -1;
  mVelocity = 0;
  for (int i = 0; i < mActiveOscs; i++) {
    mOsc[i].reset();
  }
  mVolumeEnvelope.reset();
  mFilterEnvelope.reset();
  mFilter.reset();
}

double Voice::nextSample() {
  if (!isActive) return 0.0;

  double oscSum = 0;
  double oscAvr = 1 / mActiveOscs;

  for (int i = 0; i < mActiveOscs; i++) {
    oscSum += oscAvr * mOsc[i].nextSample() * mOscVol[i];
  }

  double volumeEnvelopeValue = mVolumeEnvelope.nextSample();
  double filterEnvelopeValue = mFilterEnvelope.nextSample();

  mFilter.setCutoffMod(filterEnvelopeValue * mFilterEnvelopeAmount + mLFOValue * mLFOAmount);

  return mFilter.process(oscSum * volumeEnvelopeValue * mVelocity / 127.0);
}

void Voice::setFree() {
  isActive = false;
}
