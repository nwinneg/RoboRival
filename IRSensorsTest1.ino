// Nate Winneg
// QTR IR Sensors Initial Test

#include <QTRSensors.h>

#define EVEN_EMITTER_PIN 2
#define ODD_EMITTER_PIN 3
#define NUM_SENSORS 13
//#define TIMEOUT 2000 // amount of time after which reading is 0

QTRSensors qtr;
uint16_t sensorValues[NUM_SENSORS]; // set up array for read() method

unsigned long previousMicros = 0;
// 50,000us = 20Hz
// 5000us = 200Hz
#define TIMESTEP 5000 // for sample rate testing -- defined in micros -- 1000us = 1ms = .001s

void setup() {
  // put your setup code here, to run once:
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46}, NUM_SENSORS);
  //qtr.setTimeout(uint16_t TIMEOUT);
  qtr.setEmitterPins(ODD_EMITTER_PIN, EVEN_EMITTER_PIN); // digital pin controlling if IR LED's on or off, can set odd/even
  qtr.setNonDimmable();
  delay(100);

  pinMode(LED_BUILTIN, OUTPUT);

  // calibrate with LED indication
  digitalWrite(LED_BUILTIN, HIGH);
  for (uint16_t i = 0; i < 400; i++)
  {
    qtr.calibrate();
  }
  digitalWrite(LED_BUILTIN, LOW); 
  Serial.begin(9600);
  // print calibration minimum values
  for (uint8_t i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtr.calibrationOn.minimum[i]);
    Serial.print('\t');
  }
  Serial.println();
  
  // print calibration maximum values
  for (uint8_t i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtr.calibrationOn.maximum[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(1000);
}

void loop() {

  /* GO IF TIMESTEP */
  unsigned long currentMicros = micros();
  if (currentMicros - previousMicros >= TIMESTEP) {
    previousMicros = previousMicros + TIMESTEP;
    
  // read calibrated sensor values and obtain a measure of the line position
  // from 0 to 5000 (for a white line, use readLineWhite() instead)
  uint16_t position = qtr.readLineWhite(sensorValues);

  // print the sensor values as numbers from 0 to 1000, where 0 means maximum
  // reflectance and 1000 means minimum reflectance, followed by the line
  // position
  for (uint8_t i = 0; i < NUM_SENSORS - 1; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println(position);
  }
}
