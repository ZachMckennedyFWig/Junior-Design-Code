#include <Arduino.h>
#include <Subsystems/Closer.h>
#include <Subsystems/PillDropper.h>
#include <Subsystems/Rotary.h>
#include <Async/Subsystem.h>


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

PillDropper pill_drop;
Closer cap;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // EXAMPLE CODE

  Subsystem* first_motion[] = {new Rotary()};
  run(first_motion, 1);
  Subsystem* second_motion[] = {new PillDropper(), new Closer()};
  run(second_motion, 2);

  delay(500);
}