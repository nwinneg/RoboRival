#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55);

// 10,000us = 100Hz
#define TIMESTEP 10000 // for sample rate testing -- defined in micros -- 1000us = 1ms = .001s

unsigned long previousMicros = 0;

imu::Vector<3> accel_data;
double vel_data[3];

void setup(void) 
{
  Serial.begin(9600);
  Serial.println("Orientation Sensor Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  delay(1000);
    
  bno.setExtCrystalUse(true);
}

void loop(void) 
{
  /* GO IF TIMESTEP */
  unsigned long currentMicros = micros();
  if (currentMicros - previousMicros >= TIMESTEP) {
    previousMicros = previousMicros + TIMESTEP;
    
    /* Get accelerometer data */
    accel_data = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
    Serial.print("X_acc: ");
    Serial.print(accel_data.x(), 4);
    Serial.print("\tY_acc: ");
    Serial.print(accel_data.y(), 4);
    Serial.print("\tZ_acc: ");L
    Serial.print(accel_data.z(), 4);
    Serial.println("");

    /* Numerically integrating to get Velocity (sum) */
//    double ax = accel_data.x();
//    double ay = accel_data.y();
//    double az = accel_data.z();
//    double vel_temp[3] = {ax, ay, az};
//    vel_data[0] += vel_temp[0]; vel_data[1] += vel_temp[1]; vel_data[2] += vel_temp[2];
//    Serial.print("\tX: ");
//    Serial.print(vel_data[0], 4);
//    Serial.print("\tY: ");
//    Serial.print(vel_data[1], 4);
//    Serial.print("\tz: ");
//    Serial.print(vel_data[2], 4);
//    Serial.println("");
    
    
    /* Get a new sensor event euler angles*/ 
  sensors_event_t event; 
  bno.getEvent(&event);
//  
//  /* Display the floating point data */
//  Serial.print("X: ");
//  Serial.print(event.orientation.x, 4);
//  Serial.print("\tY: ");
//  Serial.print(event.orientation.y, 4);
//  Serial.print("Yaw Angle: ");
//  Serial.print(event.orientation.z, 4);
//  Serial.print("\tTemp: ");
//  Serial.print(bno.getTemp());
//  Serial.println("");
  }
}
