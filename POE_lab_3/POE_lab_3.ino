// Code for POE Lab 3: a line-following robot.
// By @arwensadler


// Setting up the motors:
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *myMotorleft = AFMS.getMotor(2);
Adafruit_DCMotor *myMotorright = AFMS.getMotor(4);




void setup() {

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  
  AFMS.begin();

  Serial.begin(9600);
  Serial.println("<Arduino ready!>");

  myMotorleft->run(FORWARD);
  myMotorright->run(FORWARD);
  

}


int a = 980; // Left sensor value to indicate if on line or not
int b = 980; // Right ""
int s = 0; // Speed of the motors




void loop() {
  
  
  // Setting up the sensors:
  int leftSensor = analogRead(A0);
  int rightSensor = analogRead(A1);

  Serial.print(leftSensor); Serial.print(",");
  Serial.println(rightSensor);
  
  
  recInput();


  if (leftSensor < a && rightSensor < b){
    myMotorleft->setSpeed(s);
    myMotorright->setSpeed(s);
    
  } else if (rightSensor >= b) {
    myMotorleft->setSpeed(s);
    myMotorright->setSpeed(0);
    
  } else if (leftSensor >= a) {
    myMotorleft->setSpeed(0);
    myMotorright->setSpeed(s);
    
  }

}


void recInput() {
   if (Serial.available() > 0) {    // is a character available?
      s = Serial.readString().toInt(); // read the number and set it to speed
      Serial.println(s);
    }
}
