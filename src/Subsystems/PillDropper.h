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
#include "Utils/ProductionManager.h"

#define MOTOR_INTERFACE 1
#define STEP_PIN 6
#define DIR_PIN 5

#define STEPPER_SPEED 200
#define STEPPER_ACCEL 50
#define STEPS 827           // Number of steps the motor will move, positive = clockwise

#define PILL_MAP_POS 0b00100000 // Pill dropper is in the third position

class PillDropper: public Subsystem {
    private:
        // Stepper motor connection
        //  First parameter is motor interface type, which is always 1 for motor drivers
        //  Second parameter is the stepping pin on the arduino
        //  Third parameter is the direction pin on the arduino  
        AccelStepper stepper1 = AccelStepper(MOTOR_INTERFACE, STEP_PIN, DIR_PIN);
        ProductionManager* ProdManager;

        bool completed;

    public:
        /**
        * @brief Class constructor
        */
        PillDropper(ProductionManager* arg_ProdManager) : ProdManager(arg_ProdManager){}

        /**
        * @brief method to initialize the pill dropper at startup
        * @returns true on success
        */
        bool init() override;

        /**
         * @brief Function to trigger the Pill Dropper and initiate a cycle of its motion
         */
        void trigger() override;

        /**
         * @brief Function to update the position of the Pill Dropper.
         */
        void update() override;

        /**
        * @brief method to check if the pill dropper is finished
        * @return true if completed
        */
        bool isComplete() override;
};

#endif