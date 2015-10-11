#include "MIDIReceiver.h"

MIDIReceiver::~MIDIReceiver()
{
}

void MIDIReceiver::onMessageReceived(IMidiMsg* midiMessage) {
  IMidiMsg::EStatusMsg status = midiMessage->StatusMsg();
  // We're only interested in Note On/Off messages (not CC, pitch, etc.)
  if (status == IMidiMsg::kNoteOn || status == IMidiMsg::kNoteOff) {
    mMidiQueue.Add(midiMessage);
  }
}

void MIDIReceiver::advance() {
  while (!mMidiQueue.Empty()) {
    IMidiMsg* midiMessage = mMidiQueue.Peek();
    if (midiMessage->mOffset > mOffset) break;

    IMidiMsg::EStatusMsg status = midiMessage->StatusMsg();
    int noteNumber = midiMessage->NoteNumber();
    int velocity = midiMessage->Velocity();
    // There are only note on/off messages in the queue, see ::OnMessageReceived
    if (status == IMidiMsg::kNoteOn && velocity) {
      if (!mKeyStatus[noteNumber]) {
        mKeyStatus[noteNumber] = true;
        mNumKeys++;
        noteOn(noteNumber, velocity);
      }
    } else {
      if (mKeyStatus[noteNumber]) {
        mKeyStatus[noteNumber] = false;
        mNumKeys--;
        noteOff(noteNumber, velocity);
      }
    }
    mMidiQueue.Remove();
  }
  mOffset++;
}
