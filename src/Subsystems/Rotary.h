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
#include <Utils/ProductionManager.h>

#define MOTOR_INTERFACE 1
#define STEP_PIN 12
#define DIR_PIN 5
#define INDEXER_PIN 32

#define STEPPER_SPEED 2500
#define STEPPER_ACCEL 5000
#define CLOSED_LOOP_STEPS 1800           // Number of steps the motor will move, positive = clockwise
#define DEAD_STOP_SPEED 400

#define OPEN_LOOP_STEPS 2000

#define INDEXER_MAP_POS 5

class Rotary: public Subsystem {
    private:
        // Stepper motor connection
        //  First parameter is motor interface type, which is always 1 for motor drivers
        //  Second parameter is the stepping pin on the arduino
        //  Third parameter is the direction pin on the arduino  
        AccelStepper stepper1 = AccelStepper(MOTOR_INTERFACE, STEP_PIN, DIR_PIN);
        ProductionManager* ProdManager;


        bool completed;

        enum RotStates {IDLE, ACCEL, CLOSED_LOOP_TRAVEL, DEADSTOP_PHASE, OPEN_LOOP_MOVE};

        RotStates state = RotStates::IDLE;

    public:

        /**
        * @brief Class constructor
        */
        Rotary(ProductionManager* arg_ProdManager) : ProdManager(arg_ProdManager) {}

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