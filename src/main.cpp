#include <Arduino.h>
#include <Subsystems/Closer.h>
#include <Subsystems/PillDropper.h>
#include <Subsystems/Rotary.h>
#include <Subsystems/Capper.h>
#include <Async/Subsystem.h>
#include <Servo.h>
#include <Utils/handler.h>

#define SERVO_PIN 10

Servo CapperServo;
Rotary ObjRotTable;
PillDropper ObjPillDisp;
Closer ObjCapClose;

SubsysHandler myHandler;


void setup() {
  Serial.begin(9600);
}

void loop() {

  myHandler.update(ObjCapClose, ObjPillDisp, ObjRotTable);

  delay(500);
}