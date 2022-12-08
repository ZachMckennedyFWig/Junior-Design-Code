/** 
 * Closer.h
 * author: Zach Mckennedy
 * date created: 11/17/2022
 * version: 1.0
*/

#ifndef CLOSER_H
#define CLOSER_H

#include <AccelStepper.h>
#include <Async/Subsystem.h>

#define MOTOR_INTERFACE 1
#define STEP_PIN 8
#define DIR_PIN 7

class Closer: public Subsystem {
    private:
    // Stepper motor connection
    //  First parameter is motor interface type, which is always 1 for motor drivers
    //  Second parameter is the stepping pin on the arduino
    //  Third parameter is the direction pin on the arduino  
    AccelStepper stepper1 = AccelStepper(MOTOR_INTERFACE, STEP_PIN, DIR_PIN);

    bool down;      // Stores the state of the downward motion of the closer 
    bool up;        // Stores the state of the upward motion of the closer
    long dis;       // Stores the distance left the motor has to travel

    public:
    /**
     * @brief Function to action the Closer and initiate a cycle of its motion.
     */
    virtual void action();
    /**
     * @brief Function to update the Closer during its cycle
     */
    virtual void update();
};

#endif