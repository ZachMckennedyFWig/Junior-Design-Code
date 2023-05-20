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
    direction = Directions::CCW; // Set direction for first run to CCW
    completed = true;
    Serial.println("Capper Initialized");
    myservo.write(MAX_ANGLE); // Set servo to MAX_ANGLE (Full CW)
    return true;
}

void Capper::trigger(){
    // If there is a bottle under the capper, trigger the cycle
    if(ProdManager->getBottleMap(CAPPER_MAP_POS)) {
        completed = false;      // Sets the completed state back to false to begin motion
        last_change_ms = millis(); // Record start time to avoid overflow issues
        direction = Directions::CCW;        // Set direction for first run to CCW
        target_pos = MIN_ANGLE; // Sets the target posotion to the minimum angle 
        //Serial.println("Capper Triggered");
        //Serial.print("Direction = ");
        //Serial.println(direction);
    } 
}

void Capper::update(){
    if(!completed && (millis() - last_change_ms > INC_TIME_MS)){    // If not completed and time for change
        switch (direction){                                        
            case Directions::CW:
                if(target_pos <= MIN_ANGLE){                        // If at max angle, mark complete and change direction
                    //Serial.println("Arrived at min angle");
                    direction = Directions::CCW;
                    completed = true;
                } 
                else{                                               // Otherwise, increment angle, write, and save change time
                    //Serial.print("Dir CW, Target = ");
                    //Serial.println(target_pos);
                    target_pos -= 1;
                    myservo.write(target_pos);
                    last_change_ms = millis();
                }
                break;

            case Directions::CCW:                                   // If at min angle, mark complete and change direction
                if(target_pos >= MAX_ANGLE){
                    //Serial.println("Arrived at max angle");
                    direction = Directions::CW;
                }
                else{                                               // Otherwise, decrement angle, write, and save change time
                    //Serial.print("Dir CCW, Target = ");
                    //Serial.println(target_pos);
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

bool Capper::isComplete() {
    return completed;
}