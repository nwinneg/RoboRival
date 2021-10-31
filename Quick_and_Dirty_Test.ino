#include "Servo.h"

#define TIMESTEP        50 // 100Hz
#define TRIAL_LENGTH    3000 // value in milliseconds for length of drive session

#define MOTORPIN_RL     3
#define DIRCONTROLRL    7
#define MOTORPIN_RR     9
#define DIRCONTROLRR    12

#define MOTORPIN_FL     5
#define DIRCONTROLFL    8
#define MOTORPIN_FR     6
#define DIRCONTROLFR    10

int ENCA_RL = 21;
int ENCA_RR = 2;
int ENCB_RL = 20;
int ENCB_RR = 1;

double distRL = 0; 
double distRR = 0;
double distance;

double prevTimeRL = 0;
double prevTimeRR = 0;

double speedRL;
double speedRR;
double speed_avg;

double prevMillis = 0;
int count = 0;

Servo servo1;

void readEncoderRR(void)
{
    double currTime = millis();
    int b = digitalRead(ENCB_RR);
    if (b<0) {
        distRL += 0.003048;
    }
    else {
        distRL -= 0.003048;
    }
    speedRR = 0.003048/((currTime - prevTimeRR)/1000); // m/s
    prevTimeRR = currTime;
}

void readEncoderRL(void)
{
    double currTime = millis();
    int b = digitalRead(ENCB_RL);
    if (b>0) {
        distRL += 0.003048;
    }
    else {
        distRL -= 0.003048;
    }
    speedRL = 0.003048/((currTime - prevTimeRL)*1000); // m/s
    prevTimeRL = currTime;
}

void solveSpeed(void) {
    speed_avg = (speedRR + speedRL)/2.0;
}

void solveDistance(void) {
    distance = (distRR + distRL)/2.0;
}

void writeMotor(int motor, double dutyCycle)
{
    double motorCmd = (dutyCycle/100.)*255.;
    analogWrite(motor, motorCmd);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Serial.write("Starting now...");
  //encodersSetup();
  pinMode(ENCA_RL, INPUT); pinMode(ENCB_RL, INPUT);
  pinMode(ENCA_RR, INPUT); pinMode(ENCB_RL, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA_RL), readEncoderRL, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCA_RR), readEncoderRR, RISING);
  
  //motorsSetup();
//    pinMode(MOTORPIN_FL, OUTPUT);
//    pinMode(MOTORPIN_FR, OUTPUT);
  pinMode(MOTORPIN_RL, OUTPUT);
  pinMode(MOTORPIN_RR, OUTPUT);

  // set direction control for rear motors...
  pinMode(DIRCONTROLRL, OUTPUT);
  digitalWrite(DIRCONTROLRL, HIGH);
  pinMode(DIRCONTROLRR, OUTPUT);
  digitalWrite(DIRCONTROLRR, HIGH);

  pinMode(DIRCONTROLFL, OUTPUT);
  digitalWrite(DIRCONTROLFL, HIGH);
  pinMode(DIRCONTROLFR, OUTPUT);
  digitalWrite(DIRCONTROLFR, HIGH);

  writeMotor(MOTORPIN_RR, 30);
  writeMotor(MOTORPIN_RL, 30);
  writeMotor(MOTORPIN_FR, 30);
  writeMotor(MOTORPIN_FL, 30);
  
  servo1.attach(11);
  servo1.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (millis() < TRIAL_LENGTH) {
      if (millis() - prevMillis > TIMESTEP) {
        // convert to string and add to array
        // on py side, float(data) gives numerical output
        prevMillis = millis();
        double currDist = distance;
        double currSpeed = speed_avg;

        Serial.print(currDist);
        Serial.print("\t");
        Serial.println(currSpeed);
      }
      else {
        solveSpeed();
        solveDistance();
      }
  }
  else {
      writeMotor(MOTORPIN_RR, 0);
      writeMotor(MOTORPIN_RL, 0);
      writeMotor(MOTORPIN_FR, 0);
      writeMotor(MOTORPIN_FL, 0);
  }
}
