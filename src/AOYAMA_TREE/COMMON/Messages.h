#pragma once

#include <BaseMessages.h>
#include <Sequencer.h>

// Each message is defined per board.
// Each board can listen and send different type of messages
// A message is defined by the board that generates (e.g. sensor) or display (e.g. leds) the data

// FLOWER messages:
#define FLOWER_MESSAGE_TYPES FLOWER_CALL, FLOWER_ACTIVE, FLOWER_SILENT, FLOWER_EXPLOSION, FLOWER_TOUCH, FLOWER_GYRO, FLOWER_LED

// BRANCH messages:
#define BRANCH_MESSAGE_TYPES BRANCH_STATE

// TREE messages:
#define TREE_MESSAGE_TYPES TREE_STATE

// ROCK messages:
#define ROCK_MESSAGE_TYPES ROCK_BPM

using namespace Messages;
using namespace HLMusicMachine;

enum MessageTypes
{
  BASE_MESSAGE_TYPES,
  FLOWER_MESSAGE_TYPES,
  BRANCH_MESSAGE_TYPES,
  ROCK_MESSAGE_TYPES,
  TREE_MESSAGE_TYPES
};

struct FlowerTouchMessage : public BaseMessage
{
  FlowerTouchMessage()
  {
    type = FLOWER_TOUCH;
  }
};

struct FlowerGyroMessage : public BaseMessage
{
  FlowerGyroMessage()
  {
    type = FLOWER_GYRO;
  }
};

struct FlowerLedMessage : public BaseMessage
{
  FlowerLedMessage()
  {
    type = FLOWER_LED;
  }
};

struct BranchStateMessage : public BaseMessage
{
  BranchStateMessage()
  {
    type = BRANCH_STATE;
  }
};

struct FlowerCallMessage : public BaseMessage
{
  FlowerCallMessage()
  {
    type = FLOWER_CALL;
  }
  uint32_t seed;
};

struct FlowerActiveMessage : public BaseMessage
{
  FlowerActiveMessage()
  {
    type = FLOWER_ACTIVE;
  }
  float activation = 0;
};

struct FlowerSilentMessage : public BaseMessage
{
  FlowerSilentMessage()
  {
    type = FLOWER_SILENT;
  }
};
