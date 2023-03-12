/** 
 * Closer.h
 * author: Jensen Gaither
 * date created: 3/12/2023
 * version: 2.0
*/

#ifndef CLOSER_H
#define CLOSER_H

#include <AccelStepper.h>
#include <Async/Subsystem.h>

#define MOTOR_INTERFACE 1
#define STEP_PIN 8
#define DIR_PIN 7

#define STEPPER_SPEED 400
#define STEPPER_ACCEL 500
#define STEPS 1600          // Number of steps the motor will move, positive = clockwise
#define OVERTIGHTEN 80      // Number of steps to overtighten

class Closer: public Subsystem {
    private:
    //  Stepper motor connection
    //  First parameter is motor interface type, which is always 1 for motor drivers
    //  Second parameter is the stepping pin on the arduino
    //  Third parameter is the direction pin on the arduino  
    AccelStepper stepper1 = AccelStepper(MOTOR_INTERFACE, STEP_PIN, DIR_PIN);

    bool down;      // Stores the state of the downward motion of the closer 
    bool up;        // Stores the state of the upward motion of the closer
    long dis;       // Stores the distance left the motor has to travel

    bool completed; // Stores the completion state

    public:
    /**
     * @brief method to initialize the closer at startup
     * @returns true on success
    */
    bool init() override;

    /**
     * @brief method to trigger the Closer and initiate a cycle of its motion
     */
    void trigger() override;

    /**
     * @brief method to update the Closer during its cycle
     */
    void update() override;

    /**
     * @brief method to check if the closer is finished
    */
    bool isComplete() override;
};

#endif