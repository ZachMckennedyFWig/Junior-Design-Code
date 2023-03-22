/** 
 * Subsystem.h
 * author: Zach Mckennedy
 * date created: 11/17/2022
 * version: 1.0
*/

#ifndef SUBSYSTEM_H
#define SUBSYSTEM_H

/**
 * @brief Class structure layout for each individual subsystem to inherit.
 * 
 * Creates a class with 3 public members, a boolean to tract the completion state of the subsystem,
 *  a virtual void function to action the subsystem for motion, and a virtual void function to
 *  update the state of the machine. 
 */
class Subsystem {
    public:
    
    /**
     * @brief Method that runs once during startup and can be used to set things up
     * @returns True on success
    */
    virtual bool init() = 0;
    
    /**
     * @brief Method to evaluate the completion state of the subsystem cycle. (Every child must implement the completed variable)
     * @returns The completion state of the subsystem: True -> Complete, False -> Still Running
     */
    virtual bool isComplete() = 0;

    /**
     * @brief Pure virtual function to trigger the subsystem and initiate a cycle (NON-BLOCKING)
     * @returns Nothing
     */
    virtual void trigger() = 0;

    /**
     * @brief Virtual function to update the subsystem (NON-BLOCKING). This method is safe to call at any time and will not result
     * in a cycle unless the subsystem has been previously triggered.
     * 
     * Things that might happen: stepper updates, sensor checks, error detection  
     * 
     * @returns Nothing
     */
    virtual void update() = 0;
};

#endif