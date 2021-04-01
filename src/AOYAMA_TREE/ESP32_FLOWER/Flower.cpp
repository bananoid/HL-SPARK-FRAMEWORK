#include "Flower.h"
#include "AOYAMA_TREE/COMMON/Messages.h"
#include <WiFi.h>
#include "FastLED.h"

Flower *FlowerSingleton = new Flower();

void Flower::begin(int wifiChannel, ESPSortedBroadcast::PeerRecord *peerList, int nPeers, Scheduler *runner)
{
  // Peer
  ESPSortedBroadcast::Peer::begin(wifiChannel, peerList, nPeers);

#ifndef OLEDSCREEN_DISABLED
  // Screen
  screen = new OledScreen(8, 22);
  screen->begin();
  screen->println(FlowerSingleton->peerDescription.name, 0);
  screen->println(WiFi.macAddress(), 1);
  screen->displayScreen();
  displayScreen.set(50 * TASK_MILLISECOND, TASK_FOREVER, [this]() {
    screen->sayHello(2);
    screen->displayScreen();
  });
  runner->addTask(displayScreen);
  displayScreen.enable();
#endif

  // Flower State
  flowerState = new FlowerState();
  flowerStateFrameUpdateTask.set(16 * TASK_MILLISECOND, TASK_FOREVER, [this]() {
    flowerStateFrameUpdate();
  });
  runner->addTask(flowerStateFrameUpdateTask);
  flowerStateFrameUpdateTask.enable();

  // LED
  CRGB *leds;

  leds = new CRGB[24];
  FastLED.addLeds<WS2812B, 18, GRB>(leds, 24); // top
  topRingLEDRenderer.begin(leds, 24);
  topRingLEDSynth = new LEDSynth::LEDSynth(24, &topRingLEDRenderer, runner);
  topRingLEDShaderSynth = topRingLEDSynth->addLEDShaderSynth();

  leds = new CRGB[24];
  FastLED.addLeds<WS2812B, 19, GRB>(leds, 24); // bottom
  bottomRingLEDRenderer.begin(leds, 24);
  bottomRingLEDSynth = new LEDSynth::LEDSynth(24, &bottomRingLEDRenderer, runner);
  bottomRingLEDShaderSynth = bottomRingLEDSynth->addLEDShaderSynth();
  bottomRingLEDShaderSynth->interpolationSpeed = 1;
  bottomRingLEDShaderSynth->targetState->hueRad = 0.01;
  bottomRingLEDShaderSynth->targetState->que = 0.5;
  bottomRingLEDShaderSynth->targetState->sym = 0;
  bottomRingLEDShaderSynth->targetState->speed = 0.1;

  leds = new CRGB[1];
  FastLED.addLeds<WS2812B, 5, GRB>(leds, 1); // dot
  ballDotLEDRenderer.begin(leds, 1);
  ballDotLEDSynth = new LEDSynth::LEDSynth(1, &ballDotLEDRenderer, runner);
  ballDotLEDShaderSynth = ballDotLEDSynth->addLEDShaderSynth();

  // IMU
  // imu = new IMUSensor(this);
  // imu->begin();
  // readIMU.set(10 * TASK_MILLISECOND, TASK_FOREVER, [this]() {
  //   imu->update();
  // });
  // runner->addTask(readIMU);
  // readIMU.enable();

  // touchSensor
  touchSensor = new TouchSensor(this);
  touchSensorUpdateTask.set(1 * TASK_MILLISECOND, TASK_FOREVER, [this]() {
    touchSensor->update();
  });
  runner->addTask(touchSensorUpdateTask);
  touchSensorUpdateTask.enable();
}

void Flower::update()
{
  // touchSensor->update();
}

void Flower::registerReceiveDataCB()
{
  esp_now_register_recv_cb([](const uint8_t *macaddr, const uint8_t *incomingData, int len) {
    FlowerSingleton->receiveDataCB(macaddr, incomingData, len);
  });
}

void Flower::receiveFilteredDataCB(uint8_t messageType, uint8_t sourceId, uint8_t targetId, const uint8_t *mac, const uint8_t *incomingData, int len)
{
  // Serial.printf("messageType %i sourceId %i targetId %i \n", messageType, sourceId, targetId);

  switch (messageType)
  {

  case PING:
  {
    BaseMessage pingMessage;
    memcpy(&pingMessage, incomingData, sizeof(pingMessage));
    break;
  }
  case BENCHMARK_MESSAGE:
  {
    BenchmarkMessage msg;
    memcpy(&msg, incomingData, sizeof(BenchmarkMessage));
#ifndef OLEDSCREEN_DISABLED
    screen->println("bmt:" + String(msg.time), 4);
#endif
    broadcastData(incomingData, len);
    break;
  }
  case FLOWER_CALL:
  {
    FlowerCallMessage msg;
    memcpy(&msg, incomingData, sizeof(FlowerCallMessage));
    flowerState->seed = msg.seed;
    flowerStateChanged();

    break;
  }
  case FLOWER_SILENT:
  {
    FlowerSilentMessage msg;
    memcpy(&msg, incomingData, sizeof(FlowerSilentMessage));

    flowerStateChanged();

    break;
  }

  default:
    break;
  }
}

void Flower::touchSensorOnTouch(int touchId)
{
  if (touchId < 5)
  {
    flowerState->increaseActivation();
  }
}

void Flower::onIMUOrientationData(sensors_event_t *orientationData)
{
  double x, y, z;
  x = orientationData->orientation.x;
  y = orientationData->orientation.y;
  z = orientationData->orientation.z;

  // Serial.printf("IMY", )
}

void Flower::flowerStateChanged()
{
  Serial.printf("Flower State Changed %i %i\n", flowerState->state, flowerState->seed);

  switch (flowerState->state)
  {
  case FlowerStates::SILENT:
  {
    // bottomRingLEDShaderSynth->targetState->hue = 0;
    break;
  }
  case FlowerStates::CALLING:
  {
    // bottomRingLEDShaderSynth->targetState->hue = 0.5;
    break;
  }
  }
}

void Flower::flowerStateFrameUpdate()
{
  flowerState->updateActivation();

  int nTouches = touchSensor->getCrownOnTouches();
  if (nTouches > 0)
  {
    flowerState->increaseActivation();
    Serial.printf("increaseActivation %i\n", nTouches);
  }

  bottomRingLEDShaderSynth->targetState->hue = flowerState->activation * 0.5;
  // bottomRingLEDShaderSynth->targetState->speed = map(flowerState->activation, 0.0, 1.0, 0.1, 2.0);

  // Serial.println(flowerState->activation);
}