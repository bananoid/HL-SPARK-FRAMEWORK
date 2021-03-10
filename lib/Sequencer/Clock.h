#pragma once

#include "config.h"
#include <TaskSchedulerDeclarations.h>

// Delegation: this is to allow clock tick to be called by main controller
class ClockDelegate
{
public:
    virtual void clockTick(); // virtual because it is not implemented in the class
};

class Clock : public Task
{
private:
    /* data */

public:
    Clock(Scheduler *runner);

    bool Callback();

    ClockDelegate *delegate;

    void clockTick();
    unsigned long tickCounter = 0;

    // BPM
    float getBpm();
    void setBpm(float bpm);

    float bpm = 120;
    const int clockDivider = 24;           // number of time intervals within a beat
    unsigned long clockInterval = 1000000; // default value to 1 sec
    const float minBpm = 10;
    const float maxBpm = 400;

    bool isPlaying = false;
    void play();
    void stop();
    void playStop();

    float getBpmPercentage();
    void increaseBpm(int increase);
};
