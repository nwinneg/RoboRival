/*
Nate Winneg
RoboRival  
    https://github.com/pololu/qtr-sensors-arduino
*/

/* Includes -------------------------------------------------------*/
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

/* Macros ---------------------------------------------------------*/
#define TIMESTEP    10000  // 100Hz sampling rate for now

Adafruit_BNO055 bno = Adafruit_BNO055(55);

imu::Vector<3> accelData;
imu::Vector<3> eulerData;

double vel_data;

/* Functions ------------------------------------------------------*/

void IMUSetup(void)
{
    if(!bno.begin()) {
        // some debugging print statement for now
        Serial.print("IMU not connected ... check I2C connection or wiring")
        while(1);
        // in the future we will need some queue that it isn't working
    }

    bno.setExtCrystalUse(true);
}

// function called to update accel data vec for later retrieval
void updateDataVecs(void)
{
    accelData = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
    eulerData = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
}

uint16_t getAccelX(void)
{
    uint16_t accX = accelData.x();
    return accX;
}

uint16_t getEulerPsi(void)
{
    uint16_t psi = eulerData.z();
}

// returns temperature reading
uint8_t getTemp(void)
{
    uint8_t temp = Adafruit_BNO055::getTemp();
    return temp;
}