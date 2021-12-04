
#include "Initialization.h"
using namespace std;

#include "IR.h"



//bool calibration  = false;
//bool starts_moving = true;

unsigned long startTime;
unsigned long currentTime;
unsigned long prevTime;
unsigned long currentTimePi;
//unsigned long runTime;

event_type event=NONE;
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600/*115200*/);
  setupMotors();
  setupEncoders();
  FastLED.addLeds<NEOPIXEL, 6>(leds, nleds);
  pinMode(START_PIN, INPUT);
  pinMode(CALIB_PIN, INPUT);
  pinMode(ESTOP_PIN, INPUT);
  pinMode(RESET_PIN, INPUT);
}

void loop() {
  currentTime = millis();
  currentTimePi = micros();

  ///////////////// CHECK CALIBRATION ////////////////////
//  Serial.print(checkCalibration());
  if (checkCalibration()) {
    // state goes from WAITING to SETUP
    event = UI_CALIBRATION;
    roborival_FSM(event);
    // will perform calibration and countdown
  }
  ///////////////////////////////////////////////////////
  ///////////////// CHECK START/STOP ////////////////////
  Serial.print(checkStart());
  if (checkStart()) {
    // TEMP: state goes from SETUP to COUNTDOWN
    event = UI_START;
    roborival_FSM(event);
    // will run countdRoutine()
  }
  Serial.print(checkStop());
  if (checkStop()) {
//    Serial.print(checkStop());
    // TEMP: state goes from DRIVING STRAIGHT to SETUP
    event = UI_STOP;
    roborival_FSM(event);
    // will go back to just before countdown, waiting for UI_START
  }
  ///////////////////////////////////////////////////////
  ////////////////////CHECK CDTIMER//////////////////////
//  Serial.print(checkCountdTimer());
  if (checkCountdTimer()) {
//    Serial.println("Imhere");
    // state goes from COUNTDOWN to DRIVING STRAIGHT
    event = TIMER_ENDS;
    roborival_FSM(event);
    // will run forwardRoutine()
  }
  ///////////////////////////////////////////////////////
  ////////////////////CHECK ESTOP////////////////////////
  Serial.print(checkESTOP());
  if (checkESTOP()) {
    // state goes from DRIVING FORWARD to STOPPING
    event = ESTOP;
    roborival_FSM(event);
    // will run forwardRoutine()
  }
  ////////////////////CHECK RESET////////////////////////
  if (checkReset()) {
    event = UI_RESET;
    roborival_FSM(event);
    // will run forwardRoutine()
  } 
  //////////////////CHECK if STOPPPED////////////////////
//  if (checkStopped()) {
//    // state goes from STOPPING to WAITING
//    event = STOPPED;
////    roborival_FSM(event);
//    // will reset certain variables
//  }
  prevTime = currentTime;
}


bool checkCalibration(void) {
//  Serial.println(calib_currentState);
  static bool calib_lastState = LOW;
  bool calib_currentState = LOW;
  bool eventStatus;
  
  calib_currentState = digitalRead(CALIB_PIN);
//  Serial.println(calib_currentState);
  if ((calib_currentState == HIGH) && (calib_lastState == LOW)) 
    eventStatus = true;
  else
    eventStatus = false;
  
  calib_lastState = calib_currentState;
  return eventStatus;
}

bool checkCountdTimer(void) {
//  Serial.println("checkCDTimer");
  bool eventStatus = false;
  if ((countdStatus == true) && ((millis() - countdTime) > (countdDuration*1000))) {
//    Serial.print((millis() - countdTime) > (countdDuration*1000));
    countdStatus = false;
    eventStatus = true;
  }
//  Serial.println(eventStatus);
  return eventStatus;
}

bool checkStart(void) {
//  Serial.println("checkStartStop");
  bool start_currentState = LOW;
//  bool estop_currentState = LOW;
  bool eventStatus = false;
  
  start_currentState = digitalRead(START_PIN);
//  estop_currentState = digitalRead(ESTOP_PIN);
  if (start_currentState == HIGH) {
//    Serial.println("START");
    eventStatus = true;
  }
  return eventStatus;
}

bool checkStop(void) {
//  Serial.println("checkStartStop");
  bool stop_currentState = HIGH;
//  bool estop_currentState = LOW;
  bool eventStatus = false;
  
  stop_currentState = digitalRead(START_PIN);
  if ((stop_currentState == LOW)/* && (!checkESTOP())*/) {
//    Serial.print(!checkESTOP());
//    Serial.print((stop_currentState == LOW));
    eventStatus = true;
  }

  return eventStatus;
}

bool checkESTOP(void) {
//  Serial.println("checkESTOP");
  bool estop_currentState = LOW;
  bool eventStatus = false;
  
  estop_currentState = digitalRead(ESTOP_PIN);
//  Serial.print(estop_currentState);
  if (estop_currentState == HIGH)
    eventStatus = true;
  else if (estop_currentState == LOW)
    eventStatus = false;

  return eventStatus;
}

//bool checkStopped(void) {
////  Serial.println("checkStopped");
//  bool eventStatus = false;
//  if (avgSpeedEnc == 0)
//    eventStatus = true;
//  else
//    eventStatus = false;
//  return eventStatus;
//}

bool checkReset(void) {
  bool reset_currentState = LOW;
  bool eventStatus = false;
  
  reset_currentState = digitalRead(RESET_PIN);
  if (reset_currentState == HIGH)
    eventStatus = true;
  else if (reset_currentState == LOW)
    eventStatus = false;

  return eventStatus;
}
