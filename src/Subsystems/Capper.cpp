/** 
 * Capper.cpp
 * author: Zach Mckennedy
 * date created: 11/17/2022
 * version: 1.0
*/

#include <Subsystems/Capper.h>

#define STEPPER_SPEED 400
#define STEPPER_ACCEL 500
#define STEPS 1600          // Number of steps the motor will move, positive = clockwise

void Capper::initialize(){
    completed = false;                          // Set current state back to false before motion

    stepper1.setMaxSpeed(STEPPER_SPEED);        // Sets the steppers max speed 
    stepper1.setAcceleration(STEPPER_ACCEL);    // Sets the steppers max acceleration

    stepper1.move(STEPS+80);                    // Moves the stepper enough to tighten the cap

    down = false;                               // Sets both states of motion to false. 
    up = false; 
}

void Capper::update(){
    if(!down){                          // If the downwards motion is not completed
        dis = stepper1.distanceToGo();  // Gets the distance remaining in the motion 

        if(dis > 0){                    // If there is still distance left in the downward motion
            stepper1.run();             // Move the motor
        }
        else{                           // Completed the downwards motion
            down = true;                // Set the down state to true
            stepper1.move(-STEPS);
        }
    }
    else if(!up){                       // If the upwards motion is not completed
        dis = stepper1.distanceToGo();  // Gets the distance remining in the motion

        if(dis < 0){                    // Is there is still disntance left in the upward motion
            stepper1.run();             // Move the motor
        }
        else{                           // Completed the upwards motion
            up = true;                  // Set the up state to true
        }
    }
    else if(!completed){                // Prevents setting this variable once the motion is complete
        completed = true;               // Set completed state to true, nothing happens when the motion
    }                                   //  is done.
}