#include <Arduino.h>
#include <Subsystems/Closer.h>
#include <Subsystems/PillDropper.h>
#include <Subsystems/Rotary.h>
#include <Subsystems/Capper.h>
#include <Subsystems/BottleHandler.h>
#include <Async/Subsystem.h>
#include <Servo.h>
#include <Utils/handler_recurse.h>
#include "Peripherals/EventButton.h"
#include "Peripherals/ButtonInterfaceDefs.h"

#define NUM_BOTTLES 12

bool bottle_map[8] = {1,0,0,0,0,0,0,0};

// Instantiate production manager
ProductionManager ProdManager(NUM_BOTTLES, bottle_map);

// Instantiate subsystem handler
SubsysHandler myHandler;

// Instantiate subsystems
Rotary RotaryTable(&ProdManager);
PillDropper PillDisp(&ProdManager);
Closer CapCloser(&ProdManager);
Capper CapCapper(&ProdManager);
BottleHandler BotHandle;

// Instantiate buttons
EventButton StartBtn(START_BTN_PIN, INPUT_PULLUP, LOW, EventButton::NO_LONG_PRESS);
EventButton StopBtn(STOP_BTN_PIN, INPUT_PULLUP, LOW, EventButton::NO_LONG_PRESS);
EventButton EStop(ESTOP_PIN, INPUT_PULLUP, LOW, EventButton::NO_LONG_PRESS);

enum class States {
  IDLE,
  MOVING,
  DISPENSING,
  ESTOP
};

States machine_state = States::IDLE;

// Function declarations
void startBtnClbk();
void stopBtnClbk();
void eStopClbk();

void setup() {
  Serial.begin(9600);

  // Initialize buttons
  StartBtn.init();
  StopBtn.init();
  EStop.init();

  // Link buttons with callback functions 
  StartBtn.reg_press_clbk(&startBtnClbk);
  StopBtn.reg_press_clbk(&stopBtnClbk);
  EStop.reg_press_clbk(&eStopClbk);

  // Initialize subsystems
  myHandler.init(RotaryTable, CapCapper, CapCloser, PillDisp);

  BotHandle.init();
}

void loop() {
  // Update buttons
  StartBtn.update();
  StopBtn.update();
  EStop.update();
  
  // Update subsystems
  myHandler.update(RotaryTable, CapCapper, CapCloser, PillDisp);

  switch (machine_state) {
    case States::IDLE:
      if(ProdManager.getBottlesRemaining() != 0) {
        Serial.println("Prodmanager Trigger from idle -> going to moving");
        Serial.print("Prodmanager bottles remaining: ");
        Serial.println(ProdManager.getBottlesRemaining());
        myHandler.trigger(CapCloser, CapCapper, PillDisp);
        machine_state = States::DISPENSING;
      }
      break;

    case States::DISPENSING:
      if(myHandler.isComplete(CapCloser, CapCapper, PillDisp)) {
        Serial.println("Dispensing Complete -> going to idle");
        RotaryTable.trigger();
        machine_state = States::MOVING;
      }
      break;

    case States::MOVING:
      if(RotaryTable.isComplete()) {
        Serial.println("Move Complete -> going to dispensing");
        machine_state = States::IDLE;
        ProdManager.flagCycleComplete(BotHandle.hasBottle());
      }
      break;

    default:
      break;
  }
}

void startBtnClbk() {
  Serial.println("Start button pressed");
  if(machine_state == States::IDLE) {
    ProdManager.startProduction();
  }
}

void stopBtnClbk() {
  Serial.println("Stop button pressed");
  ProdManager.stopProduction();
}

void eStopClbk() {
  Serial.println("EStop pressed");
}