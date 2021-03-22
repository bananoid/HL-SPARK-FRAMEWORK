#include "Instrument.h"
#include <Arduino.h>

namespace HLSequencer
{
  Instrument::Instrument(Scheduler *runner, int voiceCount)
  {
    voices.reserve(voiceCount);
    for (int i = 0; i < voiceCount; i++)
    {
      Voice *voice = new Voice(runner);
      voice->delegate = this;
      voices.push_back(voice);
    }
  }

  void Instrument::toggleEnabled()
  {
    isEnabled = !isEnabled;
  }

  long Instrument::getClockTime()
  {
    return delegate->getClockTime();
  }

  void Instrument::trigNote(int note, int vel, int noteLenght)
  {
    if (note != lastNote)
    {
      voiceIndex++;
    }
    voiceIndex = voiceIndex % voices.size();

    voices[voiceIndex]->noteOn(note, vel, noteLenght);

    lastNote = note;
  }

  void Instrument::noteOn(int note, int vel)
  {
  }

  void Instrument::noteOff(int note)
  {
  }

}