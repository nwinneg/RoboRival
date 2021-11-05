/*
Nate Winneg
RoboRival  
    
*/

/* Includes -------------------------------------------------------*/
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
/* Macros ---------------------------------------------------------*/
Adafruit_BNO055 bno = Adafruit_BNO055(55);

imu::Vector<3> accelData;
imu::Vector<3> eulerData;

// global variables to store IMU data -- velocity not used currently
double ax; 
double ay;
double psi;
float temperature;
double vel_data;
/* Functions ------------------------------------------------------*/
// probably want to add an indicator LED instead of a print statement
void IMUSetup(void)
{
    if(!bno.begin()) {
        // some debugging print statement for now
        Serial.print("IMU not connected ... check I2C connection or wiring");
        while(1);
        // in the future we will need some queue that it isn't working
    }

    bno.setExtCrystalUse(true);
}

void readIMU(void)
{
    accelData = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
    eulerData = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    ax = accelData.x();
    ay = accelData.y();
    psi = eulerData.z();
    temperature = bno.getTemp();
}
