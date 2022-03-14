#include "TaskScheduler.h"
#include "serial_parser.h"

//serial port parser
Task serial_task(TASK_MILLISECOND, TASK_FOREVER, &parse_message);

Scheduler scheduler;


void setup()
{
  // put your setup code here, to run once:
  Serial.begin(1000000);

  scheduler.init();
  scheduler.addTask(serial_task);


  serial_task.enable();

  // enable watchdog
}

void loop()
{
  // put your main code here, to run repeatedly:
  scheduler.execute();
}
