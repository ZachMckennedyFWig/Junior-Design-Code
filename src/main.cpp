#include <Arduino.h>
#include <Subsystems/Closer.h>
#include <Subsystems/PillDropper.h>
#include <Subsystems/Rotary.h>
#include <Subsystems/Capper.h>
#include <Async/Subsystem.h>
#include <Servo.h>
#include <Utils/handler_recurse.h>

#define NUM_BOTTLES 12
#define BOTTLE_MAP 0b10000000

ProductionManager ProdManager(NUM_BOTTLES, BOTTLE_MAP);

Rotary RotaryTable;
PillDropper PillDisp(&ProdManager);
Closer CapCloser(&ProdManager);
Capper CapCapper(&ProdManager);

SubsysHandler myHandler;

void setup() {
  Serial.begin(9600);
  myHandler.init(RotaryTable,PillDisp,CapCloser,CapCapper);
}

void loop() {

  myHandler.update(RotaryTable, PillDisp, CapCloser, CapCapper);

  delay(500);
}