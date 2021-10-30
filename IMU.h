/*
Nate Winneg
RoboRival
    This file defines variables and function definitions
    related to reading the BNO055 IMU sensor
    https://github.com/adafruit/Adafruit_BNO055/blob/master/Adafruit_BNO055.cpp
*/

#ifndef IMU
#define IMU

/* Includes -------------------------------------------------------*/

/* Macros ---------------------------------------------------------*/


/* Functions ------------------------------------------------------*/
void IMUSetup(void);

void updateDataVecs(void);

uint16_t getAccelX(void);

uint16_t getEulerPsi(void);

uint8_t getTemp(void);