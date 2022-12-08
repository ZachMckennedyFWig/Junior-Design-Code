/** 
 * PillDropper.h
 * author: Zach Mckennedy
 * date created: 11/17/2022
 * version: 1.0
*/

#ifndef PILLDROPPER_H
#define PILLDROPPER_H

#include <AccelStepper.h>
#include <Async/Subsystem.h>

#define MOTOR_INTERFACE 1
#define STEP_PIN 6
#define DIR_PIN 5

class PillDropper: public Subsystem {
    private:
        // Stepper motor connection
        //  First parameter is motor interface type, which is always 1 for motor drivers
        //  Second parameter is the stepping pin on the arduino
        //  Third parameter is the direction pin on the arduino  
        AccelStepper stepper1 = AccelStepper(MOTOR_INTERFACE, STEP_PIN, DIR_PIN);
    public:
        /**
         * @brief Function to action the Pill Dropper before it completes a cycle of its motion.
         */
        virtual void action();
        /**
         * @brief Function to update the position of the Pill Dropper.
         */
        virtual void update();
};

#endif