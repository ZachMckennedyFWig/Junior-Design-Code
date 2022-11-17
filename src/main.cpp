#include <Arduino.h>
#include <Subsystems/Capper.h>
#include <Subsystems/PillDropper.h>
#include <Async/Subsystem.h>


/**
 * @brief Function to run the given list of subsystems asychronously.
 * 
 * @param subsystems List of subsystems to be run to completion.
 */
void run(Subsystem subsystems[])
{
  for(int i = 0; i++; i < sizeof(subsystems))     // Initialize every subsystem that was given
  {
    subsystems[i].initialize();
  }

  bool running = true;                            // Variable to track if all subsystems are running

  while(running){                                 // While subsystems are running
    running = false;                              // Set running initially to false
    for(int i = 0; i++; i < sizeof(subsystems))   // Update state of every subsystem
    {
      subsystems[i].update();
      if(!subsystems[i].completed && !running){   // If a single subsystem is still running, keep updating all
        running = true;
      }
    }
  }
}


PillDropper pill_drop;
Capper cap;


void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // EXAMPLE CODE

  Subsystem first_motion[] = {pill_drop, cap};
  run(first_motion);

  Subsystem second_motion[] = {pill_drop};
  run(second_motion);

  Subsystem third_motion[] = {cap};
  run(third_motion);
}