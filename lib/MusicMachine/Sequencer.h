#pragma once

#include "Scale.hpp"
#include "MusicTheory.hpp"

#include "Instrument.h"
#include "Tracker.h"

using namespace MusicTheory;

namespace HLMusicMachine
{
  enum Type
  {
    MELODY,
    PERCUSSION
  };

  enum ArpeggioType
  {
    ArpeggioType_Eucledian,
    ArpeggioType_LFO
  };

  struct Step
  {
    int note = 1;
    int velocity = 127;
  };

  class Tracker;
  class Sequencer
  {
  private:
    int lastStepInx = 0;
    Step lastStep;
    int onCounter = 0;

  public:
    struct Parameters
    {
      int steps = 16;
      int events = 4;
      int offset = 0;

      int stepLenght = 24;

      int octave = 3;
      int noteCount = 4;
      int noteSpread = 2;
      ArpeggioType arpeggioType = ArpeggioType_Eucledian;
      int arpeggioLFO = 3;

      int chord = 0;

      int retrig = 0; // 0 is disable -1 is auto with lfo
      float retrigLFO = 32;
      int retrigLFOMin = 1;
      int retrigLFOMax = 8;

      int velocity = 127; // -1 enable lfo
      float velocityLFO = 16;
      int velocityLFOMin = 30;
      int velocityLFOMax = 127;
    };

    Type type = MELODY;
    Note percussionNote = Note(24);

    Parameters parameters;

    Tracker *tracker;

    Instrument *instrument;
    Sequencer(Tracker *tracker, Instrument *instrument);

    bool isEuclidean(int stepInx);

    void clockTick(int counter);
  };
}
