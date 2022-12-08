/** 
 * PillDropper.cpp
 * author: Zach Mckennedy
 * date created: 11/17/2022
 * version: 1.0
*/

#include <Subsystems/Rotary.h>

#define STEPPER_SPEED 500
#define STEPPER_ACCEL 100
#define STEPS 2000           // Number of steps the motor will move, positive = clockwise

void Rotary::action(){
    completed = false;                          // Set current state back to false before motion
        
    stepper1.setMaxSpeed(STEPPER_SPEED);        // Sets the steppers max speed 
    stepper1.setAcceleration(STEPPER_ACCEL);    // Sets the steppers max acceleration

    stepper1.move(-STEPS);                     // Moves the stepper 1 full rotation
}

void Rotary::update(){
        if(stepper1.distanceToGo() < 0){    // If the motion is not complete
            stepper1.run();                 // Update the motor position
        }
        else if(!completed){                // Gaurd to prevent repeatedly setting variable to the same value
            completed = true;               // Set completed state to true, nothing happens when motion is done
        }
    }