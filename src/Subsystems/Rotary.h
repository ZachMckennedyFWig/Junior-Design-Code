/** 
 * PillDropper.h
 * author: Zach Mckennedy
 * date created: 12/02/2022
 * version: 1.0
*/

#ifndef ROTARY_H
#define ROTARY_H

#include <AccelStepper.h>
#include <Async/Subsystem.h>

#define MOTOR_INTERFACE 1
#define STEP_PIN 4
#define DIR_PIN 3

class Rotary: public Subsystem {
    private:
        // Stepper motor connection
        //  First parameter is motor interface type, which is always 1 for motor drivers
        //  Second parameter is the stepping pin on the arduino
        //  Third parameter is the direction pin on the arduino  
        AccelStepper stepper1 = AccelStepper(MOTOR_INTERFACE, STEP_PIN, DIR_PIN);
    public:
        /**
         * @brief Function to initialize the Pill Dropper before it completes a cycle of its motion.
         */
        virtual void initialize();
        /**
         * @brief Function to update the position of the Pill Dropper.
         */
        virtual void update();
};

#endif