#define ENCA_RL   18
#define ENCA_RR   19
#define ENCB_RL   50
#define ENCB_RR   51

#define START_PIN   2
#define CALIB_PIN   3

using namespace std;

#include "IR.h"

// event_type is moved here for testing purpose
// otherwise the variable event would have undeclared type
typedef enum 
{
  // list out the events that can trigger things here
  UI_START,
  TIMER_ENDS,
  OBS_DETECTED,
  IMPACT_DETECTED,
  ESTOP,
  RACE_COMPLETED,
//  TURN_DETECTED,
  OBS_CLEARED,
  STOPPED,
  NONE
} event_type;

event_type event = NONE;

// wheel physical params
//float wheelRad = 0.05461; //4.3"
float wheelRad = 0.0525; //4.13"

// 36.4 rises on channel A per revolution
float encoderCountsPerRev = 36.4;
float prevTimeEncoder = 0;
int countsRL;
int countsRR;
float distRight;
float distLeft;
float distRightPrev;
float distLeftPrev;
float speedLeft;
float speedRight;
double currDistanceEnc;
double currSpeedEnc;

float setpointSpeed = 0.5;
float kp_speed = 1; float ki_speed = 1; float kd_speed = 1;

bool calibration  = false;
bool starts_moving = true;

static unsigned long lastTime = 0;
unsigned long startTime;
unsigned long currentTime;
unsigned long currentTimePi;
unsigned long runTime;

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600/*115200*/);
  setupMotors();
  setupEncoders();
  pinMode(START_PIN, INPUT);
  pinMode(CALIB_PIN, INPUT);
}

void loop() {
  currentTime = millis();
  currentTimePi = micros();

  // All events will happen after calibration is done
  if (digitalRead(CALIB_PIN) == HIGH){
    if (!calibration) {
      calibRoutine(); // set up IR and then servo
      calibration = true;
    }

    // When user presses ON/START:
    if (digitalRead(START_PIN) == HIGH){
      ////////// SPEED ////////////
      if (starts_moving) {
        setMotorPWM_All(35);
        startTime = millis();
        starts_moving = false;
      }
      if ((currentTime - startTime) > 2500) {
        setMotorPWM_All(25);
      }
      //////// LINE TRACKING ///////
      forwardRoutine(); // read IR sensors, follow line and read encoders
    } else if (digitalRead(START_PIN) == LOW) {
       stopRoutine();
    }
  }

}

//////////////////////
void encoders_TEST() {
//  currentTime = millis();
  readEncoders();
  Serial.print(currDistanceEnc);
  Serial.print("\t");
  Serial.println(currSpeedEnc);
}
///////////////////
//void FSM_TEST() {
//  if (TEST) {
//    currentTime = millis(); //tracking time
//    if (currentTime > 1000 && currentTime < 2000) {
//      event = UI_START; // start with UI_START
//    }
//    if (currentTime > 5000 && currentTime < 6000) {
//      event = TIMER_ENDS; // after about 5 sec, TIMER_ENDS becomes the event
//    }
//    if (currentTime > 8000 && currentTime < 9000) {
//      event = ESTOP; // after aboyt 8 sec, ESTOP becomes the event
//    }
//    if (currentTime > 11000 && currentTime < 12000) {
//      event = STOPPED; // after about 11 sec, STOPPED becomes the event
//    }
//    roborival_FSM(event);
//  }
//  event = NONE; // reset event
//}
