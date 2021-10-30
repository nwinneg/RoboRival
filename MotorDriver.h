/*
Nate Winneg
RoboRival
    
*/

#ifndef MOTORDRIVER
#define MOTORDRIVER

/* Includes -------------------------------------------------------*/

/* Macros ---------------------------------------------------------*/
#define MOTORPIN_FL     9
#define MOTORPIN_FR     10
#define MOTORPIN_RL     11
#define MOTORPIN_RR     12

/* Functions ------------------------------------------------------*/

void motorsSetup(void);

void writeMotor(motor, dutyCycle);
