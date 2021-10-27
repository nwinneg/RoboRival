/* Includes -------------------------------------------------------*/
#include "IR_Sensors.h"
#include "IMU.h"
#include "Encoders.h"

/* Macros ---------------------------------------------------------*/
#define Kp_steer
#define Kd_steer
#define Ki_steer

#define Kp_speed
#define Kd_speed
#define Ki_speed

void setup()
{
    IMUSetup();
    IRSensorsSetup();
    calibrateIR();
    encodersSetup();
}

void loop()
{

}