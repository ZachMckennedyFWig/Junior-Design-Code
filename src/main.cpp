#include <Arduino.h>
#include <Subsystems/Closer.h>
#include <Subsystems/PillDropper.h>
#include <Subsystems/Rotary.h>
#include <Subsystems/Capper.h>
#include <Async/Subsystem.h>
#include <Servo.h>
#include <Utils/handler_recurse.h>

#define NUM_BOTTLES 12

bool bottle_map[8] = {1,1,1,1,1,1,1,1};

ProductionManager ProdManager(NUM_BOTTLES, bottle_map);

Rotary RotaryTable;
PillDropper PillDisp(&ProdManager);
Closer CapCloser(&ProdManager);
Capper CapCapper(&ProdManager);

SubsysHandler myHandler;

void setup() {
  Serial.begin(9600);
  myHandler.init(CapCapper);
}

void loop() {
  myHandler.update(CapCapper);
  if(CapCapper.isComplete()) {
    myHandler.trigger(CapCapper);
  }
}