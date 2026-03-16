
/*
functionality
 3 button interface and 7 infusion triggers
 - 3 buttons: 
    fast-forward (ff): rotates motor forward while button is held
    stop: immediately stops any ongoing rotation
    fast-reverse (fr): rotates motor backward while button is held
 - 7 infusion triggers:
    each trigger is used for an independent infusion 
    infusions have the following variables
     - infustion duration
     - infusion vol
     - syringe internal diamter (id)
    using these variables, the speed per infusion is calculated 


**Calculations for linear rate of travel per step**
1 rotation = 1600 steps (this was used to find the rotation/step amount)
46 infusions/rotations for 1.5 inches (38.1mm) (this was used to find how many rotations per distance travled. Can use this rate for any distance)
1600 steps/1 rotation = x steps/46 rotations (This is the equation used to find steps per 1.5 inches traveled) x = 73,600 steps -----> 73,600 steps for 1.5 inches (38.1mm) traveled
If 73,600 steps = 1.5 inches, then 147,200 steps = 3 inches traveled

Empirically tested on 10-5-22
Plugged in 147200 into infusion_distance and counted the number of rotations visually as well as made sure that it traveled exactly 3 inches (76.2mm). I counted 92 rotations. Using this number, I wanted to see if 
92 rotations/x steps = 1 rotation/1600 steps (I used this formula to double check what U was visually seeing was consistent with my calculated step ratio)
x = 147200 (This number is consistent with how many steps we should have expected for this distance

Calculations for infusion rate for a BD Luer-Lok 1mL syringe
According to Chemyx site, the inner diameter of a 1mL BD plastic syringe is 4.78mm
  - 0.0557255 mm travel / uL infusion

According to Chemyx site, the inner diameter of a 3mL BD plastic syringe is 8.66mm
  - 0.0169775 mm trave l / uL infusion

 travel / step
 - 0.00051766304 mm / step (based on 76.2 mm / 147200 steps)

 steps / uL
 (1 / 0.00051766304 mm / step) * (0.0557255 mm travel / uL infusion) = 107.65 steps / uL

 12.5 uL inf 
   107.65 steps / uL * 12.5 uL = 1346 steps

 variable vol, fixed infuison duration, variable rate
*/

  #include <AccelStepper.h>
  //Define stepper motor connections
  #define dirPin 6   
  #define stepPin 5  
  
  AccelStepper stepper(1,stepPin,dirPin); //motor interface type must be set to 1 when using a driver.
 
 // button pins / parameters
  static byte pin_ff = 2;
  static byte pin_stop = 3;
  static byte pin_fr = 4;

  long button_infusion_speed = 2000;
 
 // trigger pins / parameters
  // note: include 1 element within each array for each input pin
  static byte pins_IN[]            = {   7,    8,    9,   10,   11,   12,   13};
  static int infusion_duration[]   = {2000, 2000, 2000, 2000, 2000, 2000, 1000}; // ms
  static double infusion_vol[]     = {15, 12.0, 12.5, 13.0, 13.5, 14.0,   20}; // µL
  boolean pins_IN_state[]          = {   1,    1,    1,    1,    1,    1,    1};
  boolean pins_IN_state_previous[] = {   1,    1,    1,    1,    1,    1,    1};
  double syringe_id[]              = {8.8, 4.78, 4.78, 4.78, 4.78, 4.78, 4.78}; // mm (inner diameter) 

  // ID: bd 1ml: 4.6

  int infusion_id;
  int infusion_repeats = 40; 
  int infusion_count = 0;
  int isi = 2000;
  
  // id key:
  //  - BD 1mL: 4.78
  
 // constants and variables...
  double steps_per_mm = 1/0.00051766304; // steps / mm constant
  double rsquared[7];
  double infusion_distance[7];
  long infusion_steps[7];
  long infusion_speed[7];
  unsigned long ts;
  unsigned long inf_start = 0;
  unsigned long inf_end = 0;
  

 // flags and pin states
  bool infuse = 0;
  boolean pin_ff_state = 1;
  boolean pin_ff_state_prev = 1;
  boolean pin_stop_state = 1;
  boolean pin_stop_state_prev = 1;
  boolean pin_fr_state = 1;
  boolean pin_fr_state_prev = 1;
  
 void setup(){
  Serial.begin(115200);           // set up Serial library at 9600 bps
  Serial.println("Stepper test!");

  pinMode(pin_ff,   INPUT_PULLUP); 
  pinMode(pin_stop, INPUT_PULLUP);
  pinMode(pin_fr,   INPUT_PULLUP);

 // calculate infusion speed based on infusion_duration and infustion_vol
  for (uint8_t i = 0; i <= 7; i++) { // for each pin in
    pinMode(pins_IN[i], INPUT_PULLUP);   // define pins_IN as inputs
    rsquared[i]          = (syringe_id[i]/2)*(syringe_id[i]/2);
    infusion_distance[i] = infusion_vol[i] / (3.1415926535897932384626433832795*rsquared[i]); // distance in mm travel for infusion
    infusion_steps[i]    = infusion_distance[i] * steps_per_mm; // steps / infusion
    infusion_speed[i]    = infusion_steps[i] / (infusion_duration[i]/1000);
  } 

 // wait for infusion id sent over serial before initiating script
  Serial.println("");
  Serial.println("input infusion id (1-7)");
  while (Serial.available() <= 0) {} // wait for serial input to start session
  infusion_id = Serial.parseInt();   // read serial
  Serial.print("testing infusion id: ");Serial.println(infusion_id);
  Serial.println();
  Serial.print("single infusion vol: "); Serial.println(infusion_vol[infusion_id - 1]);
  Serial.print("inter sol interval: "); Serial.println(isi);
  Serial.print("number of infusions: "); Serial.println(infusion_repeats);
  Serial.print("target vol(µL): "); Serial.println(infusion_repeats * infusion_vol[infusion_id - 1]);
  Serial.println("");

  stepper.setMaxSpeed(5000);	
  stepper.setSpeed(0); //steps per second
}

//-------------------------------------------------------------
void loop(){  
  ts = millis();

 // run pump **********
  if(infuse == 1){      // while infusion is active
    stepper.runSpeed(); // continue to run pump (speed set with insusion onset)
  } else {
    stepper.moveTo(stepper.currentPosition());
    stepper.setSpeed(0);
   // while (stepper.currentPosition() != stepper.targetPosition()) { // re
   //   stepper.runSpeedToPosition();
   // }
  }
  
  ts = millis();

  if(ts > inf_end && inf_end != 0){
    Serial.println("stop");
    infuse = 0;
    inf_end = 0;
  }

 // trigger pin infusions -------------------------------------
  if(infusion_count > infusion_repeats && infusion_count != -1){
    Serial.println();
    Serial.println("infusions complete, restart serial or upload arduino script to repeat");
    infusion_count = -1;
  }
 
    if(ts > inf_start && infusion_count < infusion_repeats && infusion_count != -1){
      infusion_count = infusion_count + 1;
      Serial.print("infusion num: ");Serial.println(infusion_count);
      stepper.setSpeed(-infusion_speed[infusion_id - 1]); 
      inf_end = ts + infusion_duration[infusion_id - 1];
      infuse = 1;
      inf_start = ts + infusion_duration[infusion_id - 1] + isi; 
    }
  

 // button infusions --------------------------------------
 
 // fast forward while holding ff button*****
  pin_ff_state = digitalRead(pin_ff);
  if(pin_ff_state < pin_ff_state_prev){
    Serial.println("fast forward");
    infusion_count = -1;
    infuse = 1;
    stepper.setSpeed(-button_infusion_speed);
  }

  if(pin_ff_state > pin_ff_state_prev){
    Serial.println("fast forward RELEASE");
    infuse = 0;
  }
  
  pin_ff_state_prev = pin_ff_state;

 // fast reverse while holding ff button*****
  pin_fr_state = digitalRead(pin_fr);
  if(pin_fr_state < pin_fr_state_prev){
    Serial.println("fast reverse");
    infusion_count = -1;
    infuse = 1;
    stepper.setSpeed(button_infusion_speed);
  }

  if(pin_fr_state > pin_fr_state_prev){
    Serial.println("fast forward RELEASE");
    infuse = 0;
  }
  
  pin_fr_state_prev = pin_fr_state;
  
 // stop mottor*****
  pin_stop_state = digitalRead(pin_stop);
  if(pin_stop_state < pin_stop_state_prev){
    Serial.println("STOP");
    infusion_count = -1;
    infuse = 0;
    inf_end = 0;
  }
  
  pin_stop_state_prev = pin_stop_state;
  
}
   
