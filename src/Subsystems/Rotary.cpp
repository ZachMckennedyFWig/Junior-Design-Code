/** 
 * PillDropper.cpp
 * author: Zach Mckennedy
 * date created: 11/17/2022
 * version: 1.0
*/

#include <Subsystems/Rotary.h>

#define STEPPER_SPEED 1000
#define STEPPER_ACCEL 750
#define STEPS 2000           // Number of steps the motor will move, positive = clockwise
#define OVERSHOOT 50         // Number of steps that the motor should overshoot to make sure bottles go in

void Rotary::action(){
    completed = false;                          // Set current state back to false before motion
        
    stepper1.setMaxSpeed(STEPPER_SPEED);        // Sets the steppers max speed 
    stepper1.setAcceleration(STEPPER_ACCEL);    // Sets the steppers max acceleration

    stepper1.move(-STEPS-OVERSHOOT);            // Moves the stepper 1 full rotation
    forwards = false;                           // Sets both states of motion to false. 
    backwards = false;
}

void Rotary::update(){
    if(!forwards){                              // If the downwards motion is not completed
        dis = stepper1.distanceToGo();          // Gets the distance remaining in the motion 

        if(dis < 0){                            // If there is still distance left in the downward motion
            stepper1.run();                     // Move the motor
        }
        else{                                   // Completed the downwards motion
            forwards = true;                    // Set the down state to true
            stepper1.move(OVERSHOOT);
        }
    }
    else if(!backwards){                        // If the upwards motion is not completed
        dis = stepper1.distanceToGo();          // Gets the distance remining in the motion

        if(dis > 0){                            // Is there is still disntance left in the upward motion
            stepper1.run();                     // Move the motor
        }
        else{                                   // Completed the upwards motion
            backwards = true;                   // Set the up state to true
        }
    }
    else if(!completed){                        // Prevents setting this variable once the motion is complete
        completed = true;                       // Set completed state to true, nothing happens when the motion
    } 
}