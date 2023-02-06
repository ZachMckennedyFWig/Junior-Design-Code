#include <Arduino.h>
#include <Subsystems/Closer.h>
#include <Subsystems/PillDropper.h>
#include <Subsystems/Rotary.h>
#include <Subsystems/Capper.h>
#include <Async/Subsystem.h>
#include <Servo.h>


#define SERVO_PIN 10

Servo CapperServo;
Rotary RotaryTable;
PillDropper PillDispenser;
Closer CapCloser;


/**
 * @brief Function to run the given list of subsystems asychronously.
 * 
 * @param subsystems List of subsystems to be run to completion.
 */
void run(Subsystem subsystems[10], int len)
{
  for(int i = 0; i < len; i++){     // Initialize every subsystem that was given
    subsystems[i].action();
  }
}

bool update(Subsystem* subsystems[], int len)
{
  for(int i = 0; i < len; i++)                  // Update state of every subsystem
  {
    Subsystem* ptr = subsystems[i];
    ptr->update();
  }
}

bool check_complete(Subsystem* subsystems[], int len)
{
  for(int i = 0; i < len; i++) {                 
    Subsystem* ptr = subsystems[i];
    if(ptr->completed == false) {
      return false;
    }
    else{
      return true;
    }
  }
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  // EXAMPLE CODE
  Subsystem *sub;
  Rotary rot;
  sub = &rot;
  
  sub->action();

  //Subsystem*Subsystem run_list[] = {};
  //run(run_list,1);

  delay(500);
}