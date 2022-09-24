// Include the AccelStepper library:
#include <AccelStepper.h>

// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define DIR_PIN 3
#define STEP_PIN 4
#define MOTOR_INTERFACE 1
#define FWD_BTN_PIN 5
#define RVS_BTN_PIN 6
#define STEP_LEAD 2000

bool fwd_btn_pressed = false;
bool rvs_btn_pressed = false;

// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(MOTOR_INTERFACE, STEP_PIN, DIR_PIN);

void setup() {
  // Configure button pins
  pinMode(FWD_BTN_PIN, INPUT_PULLUP);
  pinMode(RVS_BTN_PIN, INPUT_PULLUP);
  
  // Set the maximum speed and acceleration:
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(500);
}

void loop() {
  // Check if forward button is held or released
  if(digitalRead(FWD_BTN_PIN) == LOW) {
    fwd_btn_pressed = true;
    stepper.move(STEP_LEAD);
  }
  else if(digitalRead(FWD_BTN_PIN) == HIGH && fwd_btn_pressed) {
    fwd_btn_pressed = false;
    stepper.stop();
  }

  // Check if reverse button is held or released
  if(digitalRead(RVS_BTN_PIN) == LOW) {
    rvs_btn_pressed = true;
    stepper.move(-STEP_LEAD);
  }
  else if(digitalRead(RVS_BTN_PIN) == HIGH && rvs_btn_pressed) {
    rvs_btn_pressed = false;
    stepper.stop();
  }

  // Run the stepper motor with acceleration
  stepper.run();
}
