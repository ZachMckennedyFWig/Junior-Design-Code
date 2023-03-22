/** 
 * Capper.cpp
 * author: Jensen Gaither
 * date created: 3/12/2023
 * version: 2.0
*/

#include <Subsystems/Closer.h>

bool Closer::init(){
    completed = true;

    stepper1.setMaxSpeed(STEPPER_SPEED);        // Sets the steppers max speed 
    stepper1.setAcceleration(STEPPER_ACCEL);    // Sets the steppers max acceleration

    return true;
}

void Closer::trigger(){
    completed = false;                          // Set current state back to false before motion

    stepper1.move(STEPS+OVERTIGHTEN);                     // Moves the stepper enough to tighten the cap

    down = false;                               // Sets both states of motion to false. 
    up = false; 
}

void Closer::update(){
    if(!completed) {
        stepper1.run();
        if(!down && stepper1.distanceToGo() == 0){  // If the downwards motion is not flagged done and the distance remaining is zero
                down = true;                        // Set the down flag to true
                stepper1.move(-STEPS);              // reset motor target position back to up pos
        }
        else if(!up && stepper1.distanceToGo() == 0){   // If the upwards motion is not flagged done and the distance remaining is zero 
                up = true;                              // Set the up state to true
        }
        else{                                   // Prevents setting this variable once the motion is complete
            completed = true;                   // Set completed state to true, nothing happens when the motion
        }    
    }                                           //  is done.
}

bool Closer::isComplete() {
    return completed;
}