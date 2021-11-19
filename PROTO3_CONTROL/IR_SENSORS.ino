/*
Nate Winneg
RoboRival  
    https://github.com/pololu/qtr-sensors-arduino
*/
/* Functions ------------------------------------------------------*/
void setupIR(void)
{
  // put your setup code here, to run once:
  qtr.setTypeRC();
  //qtr.setSensorPins((const uint8_t[]){22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46}, NUM_SENSORS);
  qtr.setSensorPins((const uint8_t[]){23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 47, 49, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 46, 48},NUM_SENSORS);
  //qtr.setTimeout(uint16_t TIMEOUT);
  qtr.setEmitterPins(ODD_EMITTER_PIN, EVEN_EMITTER_PIN); // digital pin controlling if IR LED's on or off, can set odd/even
  qtr.setNonDimmable();
  delay(100);

  //pinMode(LED_BUILTIN, OUTPUT);

  // calibrate with LED indication
  //digitalWrite(LED_BUILTIN, HIGH);
  for (uint16_t i = 0; i < 400; i++)
  {
    qtr.calibrate();
  }
  //digitalWrite(LED_BUILTIN, LOW); 
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

void readIRSensors(void)
{
//  linePosition = qtr.readLineBlack(sensorValues) / 100;
  linePosition = qtr.readLineWhite(sensorValues) / 100;
//  Serial.println(linePosition);
}

void followLine(void)
{
  static float last_turningAngle = 84; // SERVO_HOME
  float new_turningAngle;
  float e_p = lineRef - linePosition;
  //float e_d = lineRefDot - (linePosition - prevLinePosition)/dT;


 // replace 84 with SERVO_HOME
  new_turningAngle = (84) + (kp_line * e_p); //+ kd_line * e_d;
  if (abs(new_turningAngle - last_turningAngle) < 3.) {
    turningAngle = last_turningAngle;
  } else {
    turningAngle = new_turningAngle;
  }
//  Serial.print(last_turningAngle);
//  Serial.print('\t');
//  Serial.print(new_turningAngle);
//  Serial.print('\t');
//  Serial.println(turningAngle);
  last_turningAngle = turningAngle;
  moveServo((int) turningAngle);
  
}
