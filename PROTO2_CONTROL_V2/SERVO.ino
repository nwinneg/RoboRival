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
#define SERVOPIN  9

Servo servo;
float servoPos;

/* Functions ------------------------------------------------------*/
void setupServo()
{
  servo.attach(SERVOPIN);
  servoPos = 90;
  servo.write(servoPos);
}
