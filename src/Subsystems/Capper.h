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

#define INC_TIME_MS 15  // Milli-seconds between servo position changes
#define MAX_ANGLE 178 // Servo Max Angle
#define MIN_ANGLE 46 // Servo Min Angle

#define SERVO_PIN 10 // Pin Servo is connected to

class Capper: public Subsystem {
    private:

    bool completed;

    Servo myservo; // Servo motor object

    enum Directions {CW, CCW};
    Directions direction;

    int8_t target_pos;
    uint64_t last_change_ms;

    public:
    /**
     * @brief Class constructor
    */
    Capper() {}
    
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