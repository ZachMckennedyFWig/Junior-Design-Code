// Belt Prototype Code, Zach Mckennedy, 9/16/22

#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);

// Set up the pins the buttons will be stored in
const int button1Pin = 2; 
const int button2Pin = 3;     
int button1State = 0;
int button2State = 0;

void setup() {
  // set up Serial library at 9600 bps
  Serial.begin(9600); 
  // Waits for Serial link to begin          
  while (!Serial);
  // Create with the default frequency 1.6KHz, Check if link has been created 
  if (!AFMS.begin()) {         
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  // Sets motor RPM
  myMotor->setSpeed(10); 
  // Sets the pins in INPUT_PULLUP since external voltage is not being applied to buttons. 
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
}

void loop() {
  // Reads the states of the buttons
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);

  // Moves the motor based on the button state
  if(button1State != 1) {myMotor->step(10, FORWARD, SINGLE);}
  else if(button2State != 1) {myMotor->step(10, BACKWARD, SINGLE);}
}
