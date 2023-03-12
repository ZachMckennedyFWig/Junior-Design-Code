#include <Arduino.h>
#include <Subsystems/Closer.h>
#include <Subsystems/PillDropper.h>
#include <Subsystems/Rotary.h>
#include <Subsystems/Capper.h>
#include <Async/Subsystem.h>
#include <Servo.h>
#include <Utils/handler_recurse.h>

Rotary RotaryTable;
PillDropper PillDisp;
Closer CapCloser;
Capper CapCapper;

SubsysHandler myHandler;

void setup() {
  Serial.begin(9600);
  myHandler.init(RotaryTable,PillDisp,CapCloser,CapCapper);
}

void loop() {

  myHandler.update(RotaryTable, PillDisp, CapCloser, CapCapper);

  delay(500);
}