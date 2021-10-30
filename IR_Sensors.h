/*
Nate Winneg
RoboRival
    This file defines variables and function definitions
    related to reading pololu qtr 13 MD sensor array
    https://github.com/pololu/qtr-sensors-arduino
*/

#ifndef IR_SENSORS
#define IR_SENSORS

/* Includes -------------------------------------------------------*/

/* Macros ---------------------------------------------------------*/


/* Functions ------------------------------------------------------*/

void IRSensorsSetup(void);

void calibrateIR(void);

void getReadingIR(void);

uint16_t getPositionIR(void);
