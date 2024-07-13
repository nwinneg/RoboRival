///////SERVO////////
/* Includes -------------------------------------------------------*/
#include "Servo.h"

/* Macros ---------------------------------------------------------*/
#define SERVOPIN  11
#define SERVO_HOME  93 // center position
#define SERVO_RANGE 30 // maximum movement in either direction

/////ENCODERS////////
#define ENCA_RL   18
#define ENCA_RR   19
#define ENCB_RL   50
#define ENCB_RR   51

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
double SpeedEncHist[5] = {0, 0, 0, 0, 0};
double avgSpeedEnc;
double currSpeedEnc;

// wheel physical params
//float wheelRad = 0.05461; //4.3"
float wheelRad = 0.0525; //4.13"

/////PI CONTROL////////////
#define START_PIN   2
#define CALIB_PIN   3
#define ESTOP_PIN   4
#define RESET_PIN   5
#define CV_CTRL_PIN   45

/////LED///////////////////
#include "FastLED.h"
#define LED_BRIGHTNESS 20
#define nleds 36
CRGB leds[nleds];

//// SPEED CONTROL////////
//float setpointSpeed;
float tempSetpointSpeed;
float setpointPWM;

float prevSpeedError;
float integralSpeedError;

float setpointSpeed = 0.8;
float kp_speed = 5; float ki_speed = 0.5; float kd_speed = 1;
float deadZonePWM = 30;

/////COUNTDOWN//////////
unsigned long countdTime = 0;
bool countdStatus = false;
int countdDuration = 10;

//////FSM//////////
typedef enum
{
  WAITING,
  SETUP,
  COUNTDOWN,
  DRIVING_STRAIGHT,
//  DRIVING_CORNER,
  AVOIDING_OBSTACLE,
//  STOPPING
} robot_state;

typedef enum 
{
  // list out the events that can trigger things here
  UI_START,
  UI_CALIBRATION,
  TIMER_ENDS,
  OBS_DETECTED,
  IMPACT_DETECTED,
  ESTOP,
  UI_STOP,
  RACE_COMPLETED,
//  TURN_DETECTED,
//  OBS_CLEARED,
//  STOPPED,
  UI_RESET,
  NONE
} event_type;
