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

// Setting up serial inputs:
const byte numChars = 32;
char input[numChars];
boolean newData = false;

int intInput = 0;
char charInput[32] = {0};

void setup() {
  AFMS.begin();

  Serial.begin(9600);
  Serial.println("a: IR sensor cutoff threshold");
  Serial.println("b: left speed");
  Serial.println("c: right speed");
  Serial.println("d: left speed increment");
  Serial.println("e: right speed increment");
  

}


int a = 985;
int b = 20;
int c = 20;
int d = 1;
int e = 1;
int speed = 10;


void loop() {
  recInput();

  if (leftSensor && rightSensor >= a) {
    b = b+d;
    c = c+e;
    myMotorleft->setSpeed(b);
    myMotorright->setSpeed(c);
    myMotorleft->run(FORWARD);
    myMotorright->run(FORWARD);
  } else if (leftSensor >= a && rightSensor < a){
    b = b-d;
    myMotorleft->setSpeed(b);
    myMotorright->setSpeed(c);
    myMotorleft->run(FORWARD);
    myMotorright->run(FORWARD);
  } else if (leftSensor < a && rightSensor >= a){
    c = c-e;
    myMotorleft->setSpeed(b);
    myMotorright->setSpeed(c);
    myMotorleft->run(FORWARD);
    myMotorright->run(FORWARD);
  }

  

}

void recInput() {
   if (Serial.available() > 0) {    // is a character available?
      speed = Serial.readString().toInt(); // read the number and set it to speed
      Serial.println(speed);
    }
}
