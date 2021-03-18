#include <Arduino.h>

#define _TASK_STD_FUNCTION
#include <TaskScheduler.h>
#include "Tree.h"

Scheduler runner;

// #include "ServerMainController.h"
// #include <Server.h>
// ServerMainController *mainController;

void setup()
{
  Serial.begin(115200);

  TreeSingleton->begin();
  TreeSingleton->beginServer(); //TODO call begin (from parent) inside beginServer

  runner.startNow();

  pinMode(2, OUTPUT);
}

void loop()
{
  runner.execute();
  delay(1000);

  // TreeSingleton->ping();
}
