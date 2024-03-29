#include "VoiceEngine.h"

VoiceEngine::VoiceEngine() {}

VoiceEngine::~VoiceEngine() {}

Voice* VoiceEngine::findFreeVoice() {
  Voice* freeVoice = NULL;
  for (int i = 0; i < NumberOfVoices; i++) {
    if (!voices[i].isActive) {
      freeVoice = &(voices[i]);
      break;
    }
  }
  return freeVoice;
}

void VoiceEngine::onNoteOn(int noteNumber, int velocity) {
  Voice* voice = findFreeVoice();
  if (!voice) {
    return;
  }
  voice->reset();
  voice->setNoteNumber(noteNumber);
  voice->mVelocity = velocity;
  voice->isActive = true;
  voice->mVolumeEnvelope.enterStage(EnvelopeGenerator::ENVELOPE_STAGE_ATTACK);
  voice->mFilterEnvelope.enterStage(EnvelopeGenerator::ENVELOPE_STAGE_ATTACK);
}

void VoiceEngine::onNoteOff(int noteNumber, int velocity) {
  // Find the voice(s) with the given noteNumber:
  for (int i = 0; i < NumberOfVoices; i++) {
    Voice& voice = voices[i];
    if (voice.isActive && voice.mNoteNumber == noteNumber) {
      voice.mVolumeEnvelope.enterStage(EnvelopeGenerator::ENVELOPE_STAGE_RELEASE);
      voice.mFilterEnvelope.enterStage(EnvelopeGenerator::ENVELOPE_STAGE_RELEASE);
    }
  }
}

double VoiceEngine::nextSample() {
  double output = 0.0;
  double lfoValue = mLFO.nextSample();
  for (int i = 0; i < NumberOfVoices; i++) {
    Voice& voice = voices[i];
    voice.setLFOValue(lfoValue);
    output += voice.nextSample();
  }
  return output;
}

void VoiceEngine::setSampleRate(double sampleRate) {
  EnvelopeGenerator::setSampleRate(sampleRate);
  for (int i = 0; i < NumberOfVoices; i++) {
    Voice& voice = voices[i];
    for (int j = 0; j < voice.mActiveOscs; j++) {
      voice.mOsc[j].setSampleRate(sampleRate);
    }
  }
  mLFO.setSampleRate(sampleRate);
}