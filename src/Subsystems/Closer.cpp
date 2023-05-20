/** 
 * Capper.cpp
 * author: Jensen Gaither
 * date created: 3/12/2023
 * version: 2.0
*/

#include <Subsystems/Closer.h>

bool Closer::init(){
    completed = true;

    stepper1.setMaxSpeed(STEPPER_SPEED);        // Sets the steppers max speed 
    stepper1.setAcceleration(STEPPER_ACCEL);    // Sets the steppers max acceleration

    Serial.println("Closer Initialized");

    pinMode(LIMIT_PIN, INPUT_PULLUP);

    return true;
}

void Closer::trigger(){
    // If there is a bottle under the closer, run the closer
    if(ProdManager->getBottleMap(CLOSER_MAP_POS) && state == CloseState::IDLE) {
        completed = false;                          // Set current state back to false before motion

        stepper1.move(STEPS+OVERTIGHTEN);                     // Moves the stepper enough to tighten the cap

        state = CloseState::LOWERING;
        Serial.println("Starting Closer");
    }
}

void Closer::update(){
    if(!completed) {
        stepper1.run();
        switch (state) {
            case CloseState::LOWERING :
                if (stepper1.distanceToGo() == 0) {
                    stepper1.move(-STEPS*2);
                    state = CloseState::RAISING;
                    Serial.println("Lowered, switching to raising");
                }
                break;
            
            case CloseState::RAISING :
                if (digitalRead(LIMIT_PIN) == LOW) {
                    stepper1.setCurrentPosition(0);
                    state = CloseState::IDLE;
                    completed = true;
                    Serial.println("Limit hit, going to idle");
                }

            default:
                break;
        }
    }                                           //  is done.
}

bool Closer::isComplete() {
    return completed;
}