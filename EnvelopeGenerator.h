#include "FastSignal.h"
using Gallant::Signal0;

#pragma once
class EnvelopeGenerator
{
public:
  EnvelopeGenerator():
    minimumLevel(0.0001),
    currentStage(ENVELOPE_STAGE_OFF),
    currentLevel(minimumLevel),
    multiplier(1.0),
    currentSampleIndex(0),
    nextStageSampleIndex(0) {
      stageValue[ENVELOPE_STAGE_OFF] = 0.0;
      stageValue[ENVELOPE_STAGE_ATTACK] = 0.01;
      stageValue[ENVELOPE_STAGE_DECAY] = 0.5;
      stageValue[ENVELOPE_STAGE_SUSTAIN] = 0.1;
      stageValue[ENVELOPE_STAGE_RELEASE] = 1.0;
    };
  ~EnvelopeGenerator();
  enum EnvelopeStage {
    ENVELOPE_STAGE_OFF = 0,
    ENVELOPE_STAGE_ATTACK,
    ENVELOPE_STAGE_DECAY,
    ENVELOPE_STAGE_SUSTAIN,
    ENVELOPE_STAGE_RELEASE,
    kNumEnvelopeStages
  };
  void enterStage(EnvelopeStage newStage);
  void setStageValue(EnvelopeStage newStage, double valToSet);
  double nextSample();
  static void setSampleRate(double newSampleRate) { sampleRate = newSampleRate; }
  void reset();
  inline EnvelopeStage getCurrentStage() const { return currentStage; }
  const double minimumLevel;
  Signal0<> beganEnvelopeCycle;
  Signal0<> finishedEnvelopeCycle;
private:
  EnvelopeStage currentStage;
  double currentLevel;
  double multiplier;
  static double sampleRate;
  double stageValue[kNumEnvelopeStages];
  void calculateMultiplier(double startLevel, double endLevel, unsigned long long lengthInSamples);
  unsigned long long currentSampleIndex;
  unsigned long long nextStageSampleIndex;
};

