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
     * @brief Variable to store the completion state of the subsystem cycle.
     */
    bool completed;
    /**
     * @brief Virtual function to action the subsystem and initiate a cycle (NON-BLOCKING)
     */
    virtual void action();

    /**
     * @brief Virtual function to update the subsystem.
     * 
     * This function also has possible error detection and sets the completion state once it has been
     *  fully updated. 
     */
    virtual void update();
};

#endif