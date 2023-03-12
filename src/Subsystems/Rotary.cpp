/** 
 * PillDropper.cpp
 * author: Jensen Gaither
 * date created: 3/12/2023
 * version: 2.0
*/

#include <Subsystems/Rotary.h>

bool Rotary::init() {
    stepper1.setMaxSpeed(STEPPER_SPEED);        // Sets the steppers max speed 
    stepper1.setAcceleration(STEPPER_ACCEL);    // Sets the steppers max acceleration
    completed = true;
    return true;
}

void Rotary::trigger(){
    completed = false;                          // Set current state back to false before motion
        
    stepper1.move(-STEPS);                     // Moves the stepper 1 full rotation
}

void Rotary::update(){
    if(!completed) {
        stepper1.run();
        if(stepper1.distanceToGo() == 0) {
            completed = true;
        }
    }
}

bool Rotary::isComplete() {
    return completed;
}