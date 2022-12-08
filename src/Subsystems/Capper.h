/**
 * CapDrop.h
 * author: Jensen Gaither
 * date created: 12/7/2022
 * version: 1.0
*/

#ifndef CAPPER_H
#define CAPPER_H

#include <Servo.h>
#include <Async/Subsystem.h>

class Capper: public Subsystem {
    private:

    Servo &myservo; // Servo motor object

    enum Directions {CW, CCW};
    Directions direction;

    int8_t target_pos;
    uint64_t last_change_ms;

    public:

    /**
     * @brief Class constructor
     * @param s a servo object instance from the parent program
    */
    Capper(Servo &s) : myservo(s) {}
    
    /**
     * @brief Function to initialize the cap dropper at startup
    */
    virtual void begin();

    /** 
     * @brief Function to action the cap dropper and initiate a cap drop cycle
    */
    virtual void action();

    /**
     * @brief Function to update the cap dropper during its cycle
    */
    virtual void update();
};

#endif