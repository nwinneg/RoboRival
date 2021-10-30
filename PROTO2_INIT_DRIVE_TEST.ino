/*
Nate Winneg
RoboRival
    This script file is intended for initial power system and component testing.
    This script initializes arrays to store speed and distance measurements as 
    strings. It then drives the robot using only the front wheels for 5 seconds 
    at a 15% duty cycle. 

    Once the 5 seconds end, it transmits the stored data 1 element at a time 
    to the RPi over serial. It first sends all of the distance data and then all 
    of the speed data. Data can be converted from string to float in python
    by the pi. 


/* Includes -------------------------------------------------------*/
#include "IR_Sensors.h"
#include "IMU.h"
#include "Encoders.h"
#include "MotorDriver.h"
#include <string>

/* Macros ---------------------------------------------------------*/
#define MAX_ARR_SIZE    4000 // for doubles this is about half the actual max
#define TIMESTEP        10000 // 100Hz
#define TRIAL_LENGTH    5000 // value in milliseconds for length of drive session

// not entirely sure this is gonna work
String speedVec[MAX_ARR_SIZE];
String distVec[MAX_ARR_SIZE];

double prevMillis = 0;
double count = 0;

// encoders only set up for rear wheels for now
void setup()
{
    encodersSetup();
    motorsSetup();

    writeMotor(MOTORPIN_FR, 15);
    writeMotor(MOTORPIN_FL, 15);
}

void loop()
{
    if (millis() < TRIAL_LENGTH) {
        if (millis() - prevMillis > TIMESTEP) {
            // convert to string and add to array
            // on py side, float(data) gives numerical output
            currDist = String(getDist(), decimalPlaces=2);
            currSpeed = String(getSpeed(), decimalPlaces=2);

            // by the end we should have a long array of ints
            distVec[count] = currDist;
            speedVec[count] = currSpeed;
        }
    }
    else {
        // kill motors 
        writeMotor(MOTORPIN_FL, 0);
        writeMotor(MOTORPIN_FR, 0);
        // serial write distance data
        for(int i = 1; i<sizeof(distVec); i++) {
            Serial.write(distVec[i]);
        }
        for(int i = 1; i<sizeof(speedVec); i++) {
            Serial.write(speedVec[i]);
        }
        // do nothing
        while(1) {}
    }
}