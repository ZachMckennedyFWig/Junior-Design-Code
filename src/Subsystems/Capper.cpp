/**
 * CapDrop.cpp
 * author: Jensen Gaither
 * date created: 12/7/2022
 * version: 1.0
*/

#include<Arduino.h>
#include<Subsystems/Capper.h>

#define INC_TIME_MS 15          // Millisecond delay between servo position changes
const int MAX_ANGLE = 172;      // Maximum Angle the servo will travel to release a cap
const int MIN_ANGLE = 35;       // Minimum Angle the servo will travel to pack up a cap

void Capper::action(){
    completed = false;      // Sets the completed state back to false to begin motion
    direction = CCW;        // Set direction for first run to CCW
    target_pos = MIN_ANGLE; // Sets the target posotion to the minimum angle 
}

void Capper::update(){
    if(!completed && (millis() - last_change_ms > INC_TIME_MS)){    // If not completed and time for change
        switch (direction){                                        
            case Directions::CW:
                if(target_pos <= MIN_ANGLE){                        // If at max angle, mark complete and change direction
                    direction = CCW;
                    completed = true;
                } 
                else{                                               // Otherwise, increment angle, write, and save change time
                    target_pos -= 1;
                    myservo.write(target_pos);
                    last_change_ms = millis();
                }
                break;

            case Directions::CCW:                                   // If at min angle, mark complete and change direction
                if(target_pos >= MAX_ANGLE){
                    direction = CW;
                }
                else{                                               // Otherwise, decrement angle, write, and save change time
                    target_pos += 1;
                    myservo.write(target_pos);
                    last_change_ms = millis();
                }
                break;
        
            default:
                break;
        }
    }
}