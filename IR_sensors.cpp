/*
Nate Winneg
RoboRival  
    https://github.com/pololu/qtr-sensors-arduino
*/

/* Includes -------------------------------------------------------*/
#include <QTRSensors.h>

/* Macros ---------------------------------------------------------*/
#define NUM_SENSORS_ONE 13
#define NUM_SENSORS_ALL 26

#define EVEN_EMITTER_PIN_LEFT   6
#define ODD_EMITTER_PIN_LEFT    7
#define EVEN_EMITTER_PIN_RIGHT  8
#define ODD_EMITTER_PIN_RIGHT   9

#define NUM_SENSORS 13

""" timestep defined in main file """
// #define TIMESTEP   10000 // 10000us = 10ms = 100Hz

QTRSensors qtrLeft;
QTRSensors qtrRight;

uint16_t sensorValuesLeft[NUM_SENSORS_ONE];
uint16_t sensorValuesRight[NUM_SENSORS_ONE];
uint16_t sensorValues[NUM_SENSORS_ALL];


/* Functions ------------------------------------------------------*/

void IRSensorsSetup(void)
{
    qtrLeft.setTypeRC();
    qtrRight.setTypeRC();

    qtrLeft.setSensorPins((const uint8_t[]){22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46}, NUM_SENSORS_ONE);
    qtrRight.setSensorPins((const uint8_t[]){23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47}, NUM_SENSORS_ONE);

    qtrLeft.setEmitterPins(ODD_EMITTER_PIN_LEFT, EVEN_EMITTER_PIN_LEFT);
    qtrRight.setEmitterPins(ODD_EMITTER_PIN_RIGHT, EVEN_EMITTER_PIN_RIGHT);

    qtrLeft.setNonDimmable();
    qtrRight.setNonDimmable();

    delay(20);

    calibration(); // takes a few seconds
    // can print max and min reflectance values here for debugging later
}

void calibrateIR(void)
{
    // can add input thresholds to this that may improve performance
    // should do some kind of indication to user while this is happening
    for (uint16_t i = 0; i < 400; i++ ) {
        qtr.calibrate();
    }
}

// this function essentially compiles the sensor readings into a large array (26x1)
void getReadingIR(void) 
{
    for (int i=0; i<NUM_SENSORS_ALL; i++) {
        sensorValues[i] = sensorValuesLeft[i];
        sensorValues[i + NUM_SENSORS_ONE] = sensorValuesRight[i];
    }
}

// this function returns the output of readLineWhite() from the qtr library for now
    // in the future this is where we'll fuse the two arrays and get a single reading
uint16_t getPositionIR(void)
{
    getReadingIR();
    uint16_t position = qtr.readLinesWhite(sensorValues);
    return position;
}
