#pragma once

#include <list>
#include <iterator>
using namespace std;

#include <Tracker.h>
#include <Track.h>
#include <Sequencer.h>
#include <MIDIInstrument.h>
using namespace HLMusicMachine;

class TrackerFactory
{
private:
  /* data */
public:
  enum TrackType
  {
    DRONE,
    BASS,
    ARP,
    CHORD,
    PAD
  };

  static void buildSong(Tracker *tracker, int nTracks)
  {
    Track *track;

    for (unsigned int i = 0; i < nTracks; i++)
    {
      TrackType type = (TrackType)i;
      int midiChannel = i + 1;

      Serial.printf("Track Type %i - midiChannel %i", type, midiChannel);

      track = new Track(tracker, new MIDIInstrument(midiChannel, tracker->runner));
      buildFactoryTrackWithSequencers(track);
      setSequncerParametersForTrackOfType(track, type);
      tracker->appendTrack(track);
    }
  }

  static Track *buildTrackWithInstrument(Tracker *tracker, Instrument *instrument)
  {
    Track *track = new Track(tracker, instrument);
    buildFactoryTrackWithSequencers(track);
    tracker->appendTrack(track);
    return track;
  }

  static void buildFactoryTrackWithSequencers(Track *track)
  {
    track->addSequencer();
    track->addSequencer();
  }

  static void setSequncerParametersForTrack(Track *track, Sequencer::Parameters paramsA, Sequencer::Parameters paramsB)
  {
    track->getSequencerAt(0)->parameters = paramsA;
    track->getSequencerAt(1)->parameters = paramsB;
  }

  static void setSequncerParametersForTrackOfType(Track *track, TrackType type)
  {

    Sequencer *sequencer;
    Sequencer::Parameters params;

    list<Sequencer *>::iterator it = track->sequencers.begin();

    switch (type)
    {
    case DRONE:
    {
      // First Sequencer
      sequencer = *it;
      sequencer->parameters = params;

      // Shared parameters
      params.stepLenght = 3;
      params.retrig = 0;
      params.retrigLFO = 64;
      params.octave = 3;
      params.noteCount = 1;
      params.noteSpread = 2;
      params.steps = 32;
      params.events = 8;
      params.offset = 0;
      params.chord = 0;
      params.velocity = -1;
      params.velocityLFO = 2;

      params.events = 1;
      params.stepLenght = 1;
      params.noteCount = 1;

      sequencer->minParameters = params;

      params.events = 16;
      params.stepLenght = 8;
      params.noteCount = 7;
      sequencer->maxParameters = params;

      sequencer->randomize();

      // Second Sequencer
      it++;
      sequencer = *it;

      // Shared parameters
      params.stepLenght = 3;
      params.retrig = 0;
      params.retrigLFO = 23;
      params.octave = 4;
      params.noteCount = 1;
      params.noteSpread = 2;
      params.steps = 32;
      params.events = 7;
      params.offset = 0;
      params.chord = 0;
      params.velocity = -1;
      params.velocityLFO = 4.2;

      sequencer->parameters = params;

      params.events = 1;
      params.stepLenght = 3;
      params.steps = 1;
      params.noteCount = 1;
      params.chord = 0;

      sequencer->minParameters = params;

      params.events = 16;
      params.stepLenght = 8;
      params.steps = 32;
      params.noteCount = 8;
      params.chord = 4;

      sequencer->maxParameters = params;

      sequencer->randomize();

      break;
    }
    case BASS:
    {
      // First Sequencer
      sequencer = *it;
      sequencer->parameters = params;

      // Shared parameters
      params.stepLenght = 3;
      params.retrig = 0;
      params.retrigLFO = 64;
      params.octave = 3;
      params.noteCount = 1;
      params.noteSpread = 2;
      params.steps = 32;
      params.events = 8;
      params.offset = 0;
      params.chord = 0;
      params.velocity = -1;
      params.velocityLFO = 2;

      params.events = 1;
      params.stepLenght = 1;
      params.noteCount = 1;

      sequencer->minParameters = params;

      params.events = 16;
      params.stepLenght = 8;
      params.noteCount = 7;
      sequencer->maxParameters = params;

      sequencer->randomize();

      // Second Sequencer
      it++;
      sequencer = *it;

      // Shared parameters
      params.stepLenght = 3;
      params.retrig = 0;
      params.retrigLFO = 23;
      params.octave = 4;
      params.noteCount = 1;
      params.noteSpread = 2;
      params.steps = 32;
      params.events = 7;
      params.offset = 0;
      params.chord = 0;
      params.velocity = -1;
      params.velocityLFO = 4.2;

      sequencer->parameters = params;

      params.events = 1;
      params.stepLenght = 3;
      params.steps = 1;
      params.noteCount = 1;
      params.chord = 0;

      sequencer->minParameters = params;

      params.events = 16;
      params.stepLenght = 8;
      params.steps = 32;
      params.noteCount = 8;
      params.chord = 4;

      sequencer->maxParameters = params;

      sequencer->randomize();
      break;
    }
    case ARP:
    {
      // First Sequencer
      sequencer = *it;
      sequencer->parameters = params;

      // Shared parameters
      params.stepLenght = 3;
      params.retrig = 0;
      params.retrigLFO = 64;
      params.octave = 3;
      params.noteCount = 1;
      params.noteSpread = 2;
      params.steps = 32;
      params.events = 8;
      params.offset = 0;
      params.chord = 0;
      params.velocity = -1;
      params.velocityLFO = 2;

      params.events = 1;
      params.stepLenght = 1;
      params.noteCount = 1;

      sequencer->minParameters = params;

      params.events = 16;
      params.stepLenght = 8;
      params.noteCount = 7;
      sequencer->maxParameters = params;

      sequencer->randomize();

      // Second Sequencer
      it++;
      sequencer = *it;

      // Shared parameters
      params.stepLenght = 3;
      params.retrig = 0;
      params.retrigLFO = 23;
      params.octave = 4;
      params.noteCount = 1;
      params.noteSpread = 2;
      params.steps = 32;
      params.events = 7;
      params.offset = 0;
      params.chord = 0;
      params.velocity = -1;
      params.velocityLFO = 4.2;

      sequencer->parameters = params;

      params.events = 1;
      params.stepLenght = 3;
      params.steps = 1;
      params.noteCount = 1;
      params.chord = 0;

      sequencer->minParameters = params;

      params.events = 16;
      params.stepLenght = 8;
      params.steps = 32;
      params.noteCount = 8;
      params.chord = 4;

      sequencer->maxParameters = params;

      sequencer->randomize();
      break;
    }
    case CHORD:
    {
      // First Sequencer
      sequencer = *it;
      sequencer->parameters = params;

      // Shared parameters
      params.stepLenght = 3;
      params.retrig = 0;
      params.retrigLFO = 64;
      params.octave = 3;
      params.noteCount = 1;
      params.noteSpread = 2;
      params.steps = 32;
      params.events = 8;
      params.offset = 0;
      params.chord = 0;
      params.velocity = -1;
      params.velocityLFO = 2;

      params.events = 1;
      params.stepLenght = 1;
      params.noteCount = 1;

      sequencer->minParameters = params;

      params.events = 16;
      params.stepLenght = 8;
      params.noteCount = 7;
      sequencer->maxParameters = params;

      sequencer->randomize();

      // Second Sequencer
      it++;
      sequencer = *it;

      // Shared parameters
      params.stepLenght = 3;
      params.retrig = 0;
      params.retrigLFO = 23;
      params.octave = 4;
      params.noteCount = 1;
      params.noteSpread = 2;
      params.steps = 32;
      params.events = 7;
      params.offset = 0;
      params.chord = 0;
      params.velocity = -1;
      params.velocityLFO = 4.2;

      sequencer->parameters = params;

      params.events = 1;
      params.stepLenght = 3;
      params.steps = 1;
      params.noteCount = 1;
      params.chord = 0;

      sequencer->minParameters = params;

      params.events = 16;
      params.stepLenght = 8;
      params.steps = 32;
      params.noteCount = 8;
      params.chord = 4;

      sequencer->maxParameters = params;

      sequencer->randomize();
      break;
    }
    case PAD:
    { // First Sequencer
      sequencer = *it;
      sequencer->parameters = params;

      // Shared parameters
      params.stepLenght = 3;
      params.retrig = 0;
      params.retrigLFO = 64;
      params.octave = 3;
      params.noteCount = 1;
      params.noteSpread = 2;
      params.steps = 32;
      params.events = 8;
      params.offset = 0;
      params.chord = 0;
      params.velocity = -1;
      params.velocityLFO = 2;

      params.events = 1;
      params.stepLenght = 1;
      params.noteCount = 1;

      sequencer->minParameters = params;

      params.events = 16;
      params.stepLenght = 8;
      params.noteCount = 7;
      sequencer->maxParameters = params;

      sequencer->randomize();

      // Second Sequencer
      it++;
      sequencer = *it;

      // Shared parameters
      params.stepLenght = 3;
      params.retrig = 0;
      params.retrigLFO = 23;
      params.octave = 4;
      params.noteCount = 1;
      params.noteSpread = 2;
      params.steps = 32;
      params.events = 7;
      params.offset = 0;
      params.chord = 0;
      params.velocity = -1;
      params.velocityLFO = 4.2;

      sequencer->parameters = params;

      params.events = 1;
      params.stepLenght = 3;
      params.steps = 1;
      params.noteCount = 1;
      params.chord = 0;

      sequencer->minParameters = params;

      params.events = 16;
      params.stepLenght = 8;
      params.steps = 32;
      params.noteCount = 8;
      params.chord = 4;

      sequencer->maxParameters = params;

      sequencer->randomize();

      break;
    }

    default:
      Serial.println("Track type not found");
      break;
    }
  }
};
