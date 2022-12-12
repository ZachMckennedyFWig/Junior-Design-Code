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
      if(ptr->completed == false && !running){    // If a single subsystem is still running, keep updating all Subsystems
        running = true;                               
      }
    }
  }
}

Servo CapperServo;    // Creates the Servo motor object

void setup() {
  Serial.begin(9600);                                   // Begin Serial writing 
  CapperServo.attach(SERVO_PIN);                        // Initialize the servo
}

Subsystem* first_motion[] = {new Rotary()};             // First block of subsystems that must be completed (Just rotary table)
Subsystem* second_motion[] = {new PillDropper(),        // Second block of subssytems that must be completed
                              new Capper(CapperServo),  //  (Pill dropper, Capper, Closer)
                              new Closer()};
int loop_count = 1;                                     // Variable to track the number of cycles the machine has done

void loop() {
  run(first_motion, 1);                                   // Run the first motion, spins the rotary table 1 bottle
  run(second_motion, loop_count > 6 ? 3 : loop_count/2);  // Run the second motion, dispenses 30 pills, drops 1 cap, closes the cap
  loop_count++;                                           // Increment the loop count
  
  delay(500);                                             // Short delay to let things settle. 
}