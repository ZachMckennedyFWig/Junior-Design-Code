/**
 * Capper.h
 * author: Jensen Gaither
 * date created: 3/12/2023
 * version: 2.0
*/

#ifndef CAPPER_H
#define CAPPER_H

#include <Arduino.h>
#include <Servo.h>
#include <Async/Subsystem.h>
#include <Utils/ProductionManager.h>

#define INC_TIME_MS 15  // Milli-seconds between servo position changes
#define MAX_ANGLE 172 // Servo Max Angle
#define MIN_ANGLE 40 // Servo Min Angle

#define SERVO_PIN 33 // Pin Servo is connected to

#define CAPPER_MAP_POS 5 // Capper is in the fifth position

class Capper: public Subsystem {
    private:

    Servo myservo; // Servo motor object
    ProductionManager* ProdManager;

    enum Directions {CW, CCW};
    Directions direction;

    uint8_t target_pos;
    uint64_t last_change_ms;

    bool completed;

    public:
    /**
     * @brief Class constructor
    */
    Capper(ProductionManager* arg_ProdManager) : ProdManager(arg_ProdManager){}
    
    /**
     * @brief Method to initialize the cap dropper at startup
    */
    bool init() override;

    /** 
     * @brief Method to trigger the cap dropper and initiate a cap drop cycle
    */
    void trigger() override;

    /**
     * @brief Method to update the cap dropper
    */
    void update() override;

    /**
     * @brief Method to check the state of the capper subsystem
     * @return True -> op finished, False -> subsytem still running
    */
    bool isComplete() override;

};

#endif