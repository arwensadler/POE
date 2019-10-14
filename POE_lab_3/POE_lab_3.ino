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


void loop() {
  recInput();
  parseInput();
  updateInput();
/*
  if (Serial.available() > 0) {
    a = Serial.read();
    Serial.println(a);
    if(Serial.read() == 'a'){
      a = Serial.parseInt();
      Serial.println(a);
    }
    // TO DEBUG: The second if statement isn't running
    else if(Serial.read() == 'b'){
      b = Serial.parseInt();
      Serial.println(b);
    }
  }
  */
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
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;
  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (rc != endMarker) {
      input[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    } else {
      input[ndx] = '\0'; // end the string
      ndx = 0;
      newData = true;
    }
    
  }
}
void parseInput(){
  if (newData == true) {
    char * strtokIndx;
  
    strtokIndx = strtok(input,"="); // Get the first part (the string)
    strcpy(charInput, strtokIndx); //Copy it to charInput
  
    strtokIndx = strtok(NULL, "="); // Continue where the last left off
    intInput = atoi(strtokIndx); // Convert to int
  }
  
}

void updateInput(){
  if (newData == true) {
    Serial.println("Received variable:");
    Serial.println(charInput);
    Serial.println("Received int:");
    Serial.println(intInput);
    newData = false;
  }
}
