/** 
 * PillDropper.cpp
 * author: Zach Mckennedy
 * date created: 11/17/2022
 * version: 1.0
*/

#include <Subsystems/PillDropper.h>

bool PillDropper::init() {
    completed = true;

    stepper1.setMaxSpeed(STEPPER_SPEED);        // Sets the steppers max speed 
    stepper1.setAcceleration(STEPPER_ACCEL);    // Sets the steppers max acceleration

    return true;
}

void PillDropper::trigger(){
    completed = false;                          // Set current state back to false before motion
    stepper1.move(STEPS);                     // Moves the stepper 1 full rotation
}

void PillDropper::update(){
    if(!completed)
    {
        stepper1.run();
        if(stepper1.distanceToGo() == 0){    // If the motion is complete
            completed = true;                // set completed flag to true
        }
    }
}

bool PillDropper::isComplete() {
    return completed;
}