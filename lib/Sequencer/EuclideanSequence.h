#pragma once
#include "SequenceGenerator.h"
namespace HLSequencer
{
  class EuclideanSequence : public SequenceGenerator
  {
  public:
    int steps = 16;
    const int maxSteps = 16;
    const int minSteps = 0;

    int events = 4;
    const int maxEvents = 16;
    const int minEvents = 0;

    int offset = 0;
    const int maxOffset = 16;
    const int minOffset = 0;

    Step *isOn(int index) override
    {
      if (events == 0)
      {
        return nullptr;
      }
      int x = (index + steps * 2 - offset) % steps;
      float step = (float)steps / (float)events;
      float fMod = fmodf(x, step);

      if (floor(fMod) == 0)
      {
        counter++;
        Step *step = new Step();
        step->note = counter % events;
        return step;
      }
      return nullptr;
    }
  };
}