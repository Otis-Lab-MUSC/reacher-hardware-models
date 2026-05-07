/*To change pump volume for 3mL BD syringe wiht ID 8.66mm, adjust the infusion volume below. 
We find setting infusion volume to 13.2uL most reliably gives 12.5uL infusions with syringe ID 8.66mm. 
To change syringe type or if you need to adjust volume per animal, see calibration file for "Pump_Calibration_030626"
*/

#include "AccelStepper.h"

// Define stepper motor connections
#define dirPin 6   
#define stepPin 5  

AccelStepper stepper(1, stepPin, dirPin); // Motor interface type must be set to 1 when using a driver.

int pump_id = 1;
static int pump_dir = 1; // Single pump direction

// Button pins / parameters
static byte pin_ff = 2;
static byte pin_home = 3;
static byte pin_fr = 4;

long button_infusion_speed = 2500;

// Trigger pins / parameters
static byte pin_IN = 13;
double infusion_duration = 2000; // ms
double infusion_vol = 13.2; // µL
boolean pin_IN_state = 1;
boolean pin_IN_state_previous = 1;
double syringe_id = 9; // mm (inner diameter)

// Constants and variables...
double steps_per_mm = 1 / 0.00051766304; // steps / mm constant
double rsquared;
double infusion_distance;
double infusion_speed_denom;
double infusion_steps;
double infusion_speed;
unsigned long ts;
unsigned long inf_end = 0;

// Flags and pin states
bool infuse = 0;
boolean pin_ff_state = 1;
boolean pin_ff_state_prev = 1;
boolean pin_home_state = 1;
boolean pin_home_state_prev = 1;
boolean pin_fr_state = 1;
boolean pin_fr_state_prev = 1;

// New variables for stop button home functions
unsigned long homePressedTime = 0;
bool homePressed = false;
bool setHomeHandled = false;
bool moveHomeHandled = false;
unsigned long setHomeThreshold = 100;
unsigned long moveHomeThreshold = 1000;
long homePosition = 0;


void setup() {
  Serial.begin(115200); // Set up Serial library at 115200 bps
  Serial.println("pump on");

  pinMode(pin_ff, INPUT_PULLUP); 
  pinMode(pin_home, INPUT_PULLUP);
  pinMode(pin_fr, INPUT_PULLUP);

  // Calculate infusion speed based on infusion_duration and infusion_vol
  pinMode(pin_IN, INPUT_PULLUP); // Define pin_IN as input
  rsquared = (syringe_id / 2) * (syringe_id / 2);
  infusion_distance = infusion_vol / (3.1415926535897932384626433832795 * rsquared); // Distance in mm travel for infusion
  infusion_steps = infusion_distance * steps_per_mm; // Steps / infusion
  infusion_speed_denom = infusion_duration / 1000;
  infusion_speed = infusion_steps / infusion_speed_denom;

  Serial.print("infusion vol: "); Serial.println(infusion_vol);
  Serial.print("infusion dur: "); Serial.println(infusion_duration);
  Serial.print("infusion distance: "); Serial.println(infusion_distance);
  Serial.print("infusion steps: "); Serial.println(infusion_steps);
  Serial.print("infusion_speed_denom: "); Serial.println(infusion_speed_denom);
  Serial.print("infusion_speed: "); Serial.println(infusion_speed);
  Serial.println("");
  
  stepper.setSpeed(0); // Steps per second
  stepper.setMaxSpeed(5000);  

}

void loop() {  
  ts = millis();

  // Run pump
  if (infuse == 1) { // While infusion is active
    stepper.runSpeed(); // Continue to run pump (speed set with infusion onset)
  } else {
    stepper.moveTo(stepper.currentPosition());
    stepper.setSpeed(0);
  }
  
  if (ts > inf_end && inf_end != 0) {
    Serial.println("stop");
    infuse = 0;
    inf_end = 0;
  }

  // Trigger pin infusion
  pin_IN_state = digitalRead(pin_IN);
  if (pin_IN_state < pin_IN_state_previous && !infuse) {
    Serial.print("input pin: ");
    Serial.println(pin_IN);
    stepper.setSpeed(pump_dir * infusion_speed); 
    inf_end = ts + infusion_duration;
    infuse = 1;
  }
  pin_IN_state_previous = pin_IN_state;

  // Button infusions

  // Fast forward while holding ff button
  pin_ff_state = digitalRead(pin_ff);
  if (pin_ff_state < pin_ff_state_prev) {
    Serial.println("fast forward");
    infuse = 1;
    stepper.setSpeed(button_infusion_speed);
  }

  if (pin_ff_state > pin_ff_state_prev) {
    Serial.println("fast forward RELEASE");
    infuse = 0;
  }
  
  pin_ff_state_prev = pin_ff_state;

  // Fast reverse while holding fr button
  pin_fr_state = digitalRead(pin_fr);
  if (pin_fr_state < pin_fr_state_prev) {
    Serial.println("fast reverse");
    infuse = 1;
    stepper.setSpeed(-button_infusion_speed);
  }

  if (pin_fr_state > pin_fr_state_prev) {
    Serial.println("fast reverse RELEASE");
    infuse = 0;
  }
  
  pin_fr_state_prev = pin_fr_state;
  
  // Return home
  pin_home_state = digitalRead(pin_home);

  if (pin_home_state < pin_home_state_prev && !homePressed) {
    homePressedTime = millis ();
    homePressed = true;
    Serial.println ("Home button");
  }

  // Check if the home button was released
  if (pin_home_state > pin_home_state_prev && homePressed) {
    homePressed = false;
    unsigned long pressDuration = millis () - homePressedTime;
    Serial.println ("Home button released.");
    
    //If the button was pressed for less than 1 second, set the home position
    if (pressDuration > setHomeThreshold && pressDuration <= moveHomeThreshold) {
      homePosition = stepper.currentPosition ();
      Serial.println ("Home position set to " + String (homePosition));
      setHomeHandled = true;
    }
    
    //If the button was pressed for longer than 1 second, move to the home position
    else if (pressDuration > moveHomeThreshold && setHomeHandled && !moveHomeHandled) {
      Serial.println ("Moving to home position.");
      stepper.moveTo (homePosition);
      moveHomeHandled = true;
    }

    //If no home position is set, prompt the user to set it first
    else if (pressDuration > moveHomeThreshold && !setHomeHandled) {
      Serial.println ("No home position. Set home position first.");
    }
  }

  pin_home_state_prev = pin_home_state;
  
  if (moveHomeHandled) {
    long currentPosition = stepper.currentPosition ();
    if (currentPosition < homePosition) {
      stepper.setSpeed (button_infusion_speed);
      infuse = 1;
    }

    else if (currentPosition > homePosition) {
      stepper.setSpeed (-button_infusion_speed);
      infuse = 1;
    }

    if (currentPosition == homePosition) {
      infuse = 0;
      Serial.println ("Home position reached");
      moveHomeHandled = false;
    }
  }
  
  // Check for serial commands
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim(); // Remove any trailing whitespace or newline characters
    if (command == "START" && !infuse) {
      Serial.println("Serial command: START");
      stepper.setSpeed(pump_dir * infusion_speed); 
      inf_end = ts + infusion_duration;
      infuse = 1;
    }
  }
}



