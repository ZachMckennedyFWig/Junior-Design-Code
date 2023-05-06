/** 
 * PillDropper.h
 * author: Zach Mckennedy
 * date created: 3/12/2023
 * version: 2.0
*/

#ifndef ROTARY_H
#define ROTARY_H

#include <AccelStepper.h>
#include <Async/Subsystem.h>

#define MOTOR_INTERFACE 1
#define STEP_PIN 12
#define DIR_PIN 5

#define STEPPER_SPEED 5000
#define STEPPER_ACCEL 5000
#define STEPS -2000           // Number of steps the motor will move, positive = clockwise


class Rotary: public Subsystem {
    private:
        // Stepper motor connection
        //  First parameter is motor interface type, which is always 1 for motor drivers
        //  Second parameter is the stepping pin on the arduino
        //  Third parameter is the direction pin on the arduino  
        AccelStepper stepper1 = AccelStepper(MOTOR_INTERFACE, STEP_PIN, DIR_PIN);

        bool completed;
    public:
        /**
         * @brief method to initalize the rotary table at boot
        */
        bool init() override;

        /**
         * @brief method to action the rotary table and initiate a cycle of its motion
         * 
         */
        void trigger() override;

        /**
         * @brief method to update the position of the rotary table.
         */
        void update()override;

        /**
         * @brief method to check the status of the rotary tabel
         * @return true if motion is finished
        */
        bool isComplete() override;
};

#endif