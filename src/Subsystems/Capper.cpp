/**
 * CapDrop.cpp
 * author: Jensen Gaither
 * date created: 12/7/2022
 * version: 1.0
*/

#include<Arduino.h>
#include<Subsystems/Capper.h>

#define INC_TIME_MS 15  // Milli-seconds between servo position changes
#define MAX_ANGLE 178
#define MIN_ANGLE 46

void Capper::begin(){
    myservo.write(MAX_ANGLE); // Set servo to MAX_ANGLE (Full CW)
    direction = Directions::CCW; // Set direction for first run to CCW
}

void Capper::action(){
    completed = false;      // Sets the completed state back to false to begin motion
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