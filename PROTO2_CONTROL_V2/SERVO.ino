/*
Nate Winneg
RoboRival  
    This file provides functions to interface with servo motor
    90 is servo central position
    https://github.com/pololu/qtr-sensors-arduino
*/

/* Includes -------------------------------------------------------*/
#include "Servo.h"

/* Macros ---------------------------------------------------------*/
#define SERVOPIN  11
#define SERVO_HOME  82 // center position
#define SERVO_RANGE 10 // maximum movement in either direction

Servo servo;

/* Functions ------------------------------------------------------*/
void setupServo()
{
  servo.attach(SERVOPIN);
  servo.write(SERVO_HOME);
}

void moveServo(int servoPOS) {
  // use this function to restrain the input position
  if (servoPOS > (SERVO_HOME + SERVO_RANGE) || servoPOS < (SERVO_HOME - SERVO_RANGE)) {
    Serial.print("Out of steering range\n");
    // other stuff
  } else {
    servo.write(servoPOS);
  }
}
