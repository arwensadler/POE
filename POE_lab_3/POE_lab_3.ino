// Code for POE Lab 3: a line-following robot.
// By @arwensadler


// Setting up the motors:
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *myMotorleft = AFMS.getMotor(3);
Adafruit_DCMotor *myMotorright = AFMS.getMotor(4);

// Setting up the sensors:
int leftSensor = A0;
int rightSensor = A1;


void setup() {
  AFMS.begin();

  Serial.begin(9600);
  Serial.println("<Arduino ready!>");

  myMotorleft->run(FORWARD);
  myMotorright->run(FORWARD);
  

}


int a = 970; // Sensor value to indicate if on line or not
int s = 10;


void loop() {
  recInput();

  if (leftSensor && rightSensor >= a) {
   // Straigt condition
    myMotorleft->setSpeed(s);
    myMotorright->setSpeed(s);
    
  } else if (leftSensor >= a && rightSensor < a){
    // Left turn condition
    myMotorleft->setSpeed(0);
    myMotorright->setSpeed(s+10);
 
  } else if (leftSensor < a && rightSensor >= a){
    // Right turn condition
    myMotorleft->setSpeed(s+10);
    myMotorright->setSpeed(0);
    
  } else {
    for(int i = 0; i <= 1; i++){
    Serial.println("Please put me on the line!");
  }

  

}
}

void recInput() {
   if (Serial.available() > 0) {    // is a character available?
      s = Serial.readString().toInt(); // read the number and set it to speed
      Serial.println(s);
    }
}
