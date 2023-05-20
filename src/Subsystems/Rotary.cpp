/** 
 * PillDropper.cpp
 * author: Jensen Gaither
 * date created: 3/12/2023
 * version: 2.0
*/

#include <Subsystems/Rotary.h>

bool Rotary::init() {
    stepper1.setMaxSpeed(STEPPER_SPEED);        // Sets the steppers max speed 
    stepper1.setAcceleration(STEPPER_ACCEL);    // Sets the steppers max acceleration
    stepper1.setSpeed(DEAD_STOP_SPEED);
    stepper1.setPinsInverted(true, false, false);

    pinMode(INDEXER_PIN, INPUT_PULLUP);

    completed = true;

    Serial.println("Rotary Table Initialized");
    return true;
}

void Rotary::trigger(){
        if(state == RotStates::IDLE) {
            completed = false;                          // Set current state back to false before motion
            
            // Differentiate behavior based on open vs closed loop
            if(ProdManager->getBottleMap(INDEXER_MAP_POS-1)) {
                stepper1.move(CLOSED_LOOP_STEPS);                     // Moves the stepper 1 full rotation
                state = RotStates::ACCEL;
            }
            else {
                stepper1.move(OPEN_LOOP_STEPS);
                state = RotStates::OPEN_LOOP_MOVE;
            }
            
        }
    }

void Rotary::update(){
    if(!completed) {
        switch (state) {
            case RotStates::ACCEL:
                stepper1.run();
                //Serial.print("In ACCEL state ");
                //Serial.println(stepper1.speed());
                if(stepper1.speed() >= STEPPER_SPEED-(STEPPER_SPEED/4)) {
                    //Serial.println("Accel finished, going to planned move");
                    state = RotStates::CLOSED_LOOP_TRAVEL;
                }
                break;
            
            case RotStates::CLOSED_LOOP_TRAVEL:
                stepper1.run();
                if(stepper1.speed() <= DEAD_STOP_SPEED) {
                    //Serial.println("Deadstop speed reached, going to deadstop phase");
                    state = RotStates::DEADSTOP_PHASE;
                    stepper1.runSpeed();
                }
                break;

            case RotStates::DEADSTOP_PHASE:
                stepper1.runSpeed();
                if(digitalRead(INDEXER_PIN) == LOW) {
                    //Serial.println("Indexer Hit -> stopping");
                    stepper1.setCurrentPosition(0);
                    state = RotStates::IDLE;
                    completed = true;
                }
                break;
            
            case RotStates::OPEN_LOOP_MOVE:
                stepper1.run();
                if(stepper1.distanceToGo() == 0) {
                    state = RotStates::IDLE;
                    completed = true;
                }
                break;

            default:
                break;
        }
    }
}

bool Rotary::isComplete() {
    return completed;
}