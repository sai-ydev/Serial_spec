#include <Arduino.h>
#include "TaskScheduler.h"

void t1Callback();

Task t1(1000, TASK_FOREVER, &t1Callback);

Scheduler scheduler;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(1000000);

  scheduler.init();

  // enable watchdog
}

void loop()
{
  // put your main code here, to run repeatedly:
  scheduler.execute();
}
