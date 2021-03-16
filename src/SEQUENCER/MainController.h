#pragma once //to prevent reimport (singleton)

#include <Arduino.h>

#include "config.h"
#include <TaskSchedulerDeclarations.h>

#include <Sequencer.h>
#include <Bounce2.h>

class MainController
{
private:
    /* data */
public:
    MainController(Scheduler *runner);
    void update();
    Bounce2::Button startStopButton = Bounce2::Button();

    HLSequencer::Sequencer *sequencer;
};
