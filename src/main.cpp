#include <Arduino.h>
#include <Subsystems/Closer.h>
#include <Subsystems/PillDropper.h>
#include <Subsystems/Rotary.h>
#include <Subsystems/Capper.h>
#include <Async/Subsystem.h>
#include <Servo.h>

#define SERVO_PIN 10

/**
 * @brief Function to run the given list of subsystems asychronously.
 * 
 * @param subsystems List of subsystems to be run to completion.
 */
void run(Subsystem* subsystems[], int len)
{
  for(int i = 0; i < len; i++)     // Initialize every subsystem that was given
  {
    Subsystem* ptr = subsystems[i];
    ptr->action();
  }

  bool running = true;                            // Variable to track if all subsystems are running

  while(running){   
    running = false;                              // While subsystems are running                       
    for(int i = 0; i < len; i++)                  // Update state of every subsystem
    {
      Subsystem* ptr = subsystems[i];
      ptr->update();
      if(ptr->completed == false && !running){   // If a single subsystem is still running, keep updating all
        running = true;
      }
    }
  }
}

Servo CapperServo;

void setup() {
  Serial.begin(9600);
  CapperServo.attach(SERVO_PIN);
}

void loop() {
  // EXAMPLE CODE

  Subsystem* first_motion[] = {new Rotary()};
  run(first_motion, 1);
  Subsystem* second_motion[] = {new PillDropper(), new Closer(), new Capper(CapperServo)};
  run(second_motion, 3);

  delay(500);
}