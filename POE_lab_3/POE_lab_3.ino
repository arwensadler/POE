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
  Serial.print("a: left speed adjustment");
  Serial.println("b: right speed adjustment");

}

void loop() {
  myMotorleft->setSpeed(50);
  myMotorright->setSpeed(50);
  myMotorleft->run(FORWARD);
  myMotorright->run(FORWARD);

}
