/**
 * Capper.cpp
 * author: Jensen Gaither
 * date created: 3/12/2023
 * version: 2.0
*/

#include<Subsystems/Capper.h>

bool Capper::init(){
    myservo.attach(SERVO_PIN);
    delay(15);
    myservo.write(MAX_ANGLE); // Set servo to MAX_ANGLE (Full CW)
    direction = Directions::CCW; // Set direction for first run to CCW
    completed = true;
    return true;
}

void Capper::trigger(){
    completed = false;      // Sets the completed state back to false to begin motion
    last_change_ms = millis() - INC_TIME_MS; // Record start time to avoid overflow issues
}

void Capper::update(){
    if(!completed && (millis() - last_change_ms > INC_TIME_MS)){    // If not completed and time for change
        switch (direction){                                         
            case Directions::CW:
                if(target_pos == MAX_ANGLE){                        // If at max angle, mark complete and change direction
                    direction = Directions::CCW;
                } 
                else{                                               // Otherwise, increment angle, write, and save change time
                    target_pos = target_pos - 1;
                    myservo.write(target_pos);
                    last_change_ms = millis();
                }
                break;

            case Directions::CCW:                                   // If at min angle, mark complete and change direction
                if(target_pos == MIN_ANGLE){
                    completed = true;
                    direction = Directions::CW;
                }
                else{                                               // Otherwise, decrement angle, write, and save change time
                    target_pos = target_pos - 1;
                    myservo.write(target_pos);
                    last_change_ms = millis();
                }
                break;
        
            default:
                break;
        }
    }
}

bool Capper::isComplete() {
    return completed;
}