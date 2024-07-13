/*
Nate Winneg
RoboRival  
    https://github.com/pololu/qtr-sensors-arduino
*/

/* Includes -------------------------------------------------------*/

/* Macros ---------------------------------------------------------*/



//typedef enum 
//{
//  // list out the events that can trigger things here
//  UI_START,
//  UI_CALIBRATION,
//  TIMER_ENDS,
//  OBS_DETECTED,
//  IMPACT_DETECTED,
//  ESTOP,
//  UI_STOP,
//  RACE_COMPLETED,
////  TURN_DETECTED,
//  OBS_CLEARED,
//  STOPPED,
//  UI_RESET,
//  NONE
//} event_type;

/* Functions ------------------------------------------------------*/

void roborival_FSM (event_type newEvent) {
  static robot_state currentState = WAITING;
  robot_state nextState;
//  Serial.print(currentState);
  switch (currentState)
  {
    case WAITING:
      switch (newEvent) {
        case UI_CALIBRATION:
          Serial.println("Event UI_CALIBRATION");
          waiting_led(false);
          nextState = SETUP;
          setLEDColor(CRGB::Yellow);
          calibRoutine(); // 10 secs
          setLEDColor(CRGB::HotPink);
          digitalWrite(CV_CTRL_PIN, HIGH);
          break;
        default:
          waiting_led(true);
//          Serial.println("ENTERED WAITING State");
          digitalWrite(CV_CTRL_PIN, HIGH);
//          wait4setting();
          nextState = currentState;
          break;
      }
      break;
    case SETUP:
      switch (newEvent) {
        case UI_START:
          Serial.println("Event UI_START");
          Serial.print("The set speed is ");
          Serial.println(setpointSpeed);
          nextState = COUNTDOWN;
          countdRoutine();
          setLEDColor(CRGB::Red);
          countdown_led(true);
          break;
        case UI_RESET:
          Serial.println("Event UI_RESET");
          digitalWrite(CV_CTRL_PIN, HIGH);
          nextState = WAITING;
          break;
        default:
//          Serial.println("ENTERED SETUP STATE");
          nextState = currentState;
          break;
      }
      break;
    case COUNTDOWN:
      switch (newEvent) {
        case TIMER_ENDS:
          Serial.println("Event TIMER_ENDS");
          nextState = DRIVING_STRAIGHT;
          countdown_led(false);
//          forwardRoutine(); // read IR sensors, follow line and read encoders
          startDrivingTime = millis();
          digitalWrite(CV_CTRL_PIN, LOW);
          break;
        case UI_RESET:
//          Serial.println("Event UI_RESET");
          digitalWrite(CV_CTRL_PIN, HIGH);
          nextState = WAITING;
          break;
        default:
//          Serial.print("Entered COUNTDOWN State\n");
//          Serial.print(currentState);
          countdown_led(true);
          nextState = currentState;
          break;
      }
      break; 
    case DRIVING_STRAIGHT:
      switch (newEvent) {
//        case OBS_DETECTED:
//          nextState = AVOIDING_OBSTACLE;
//          avoidRoutine();
//          break;
//        case IMPACT_DETECTED:
//          nextState = WAITING;
//          stopRoutine();
//          break;
        case ESTOP:
          Serial.println("Event ESTOP");
          nextState = WAITING;
          stopRoutine();
          servo.detach();
          break;
        case UI_STOP:
          Serial.println("UI_STOP");
          stopRoutine();
          nextState = SETUP;
          setLEDColor(CRGB::HotPink);
          break;
        case RACE_COMPLETED:
          nextState = WAITING;
          stopRoutine();
          break;
//        case TURN_DETECTED:
//          nextState = DRIVING_CORNER;
//          stopRoutine();
//          break;
        default:
          setLEDColor(CRGB::Green);
//          Serial.print("Entered DRIVING_STRAIGHT State\n");
          forwardRoutine();
          nextState = currentState;
          break;
      }
      break;
      
//    case DRIVING_CORNER:
//    break;
    
//    case AVOIDING_OBSTACLE:
//      switch (newEvent) {
//        case OBS_CLEARED:
//          nextState = DRIVING_STRAIGHT;
//          forwardRoutine();
//          break;
//        case ESTOP:
//          Serial.print("Event ESTOP\n");
//          nextState = STOPPING;
//          stopRoutine();
//          break;
//        default:
//          nextState = currentState;
//      }
//      break;
    
//    case STOPPING:
//      switch (newEvent) {
//        case STOPPED:
//          Serial.print("Event STOPPED\n");
//          nextState = WAITING;
//          break;
//        default:
////          Serial.print("Entered STOPPING State\n");
//          nextState = currentState;
//          break;
//      }
//      break;
  }
//  Serial.println(nextState);
  currentState = nextState;
}

void calibRoutine() {
  Serial.println("Start calibrating");
  setupIR();
  setupServo();
  Serial.println("Calibrated");
}

void countdRoutine() {
  countdTime = millis();
  countdStatus = true;
  Serial.println("Counting down");
}

void forwardRoutine() {
//  Serial.println("Going forward (reading encoders; reading IR sensors; following line)");
  readEncoders();
  Serial.print(currentTimePi);
  Serial.print('\t');
  Serial.print((int) (currDistanceEnc*1000));
  Serial.print('\t');
  Serial.print((int) (currSpeedEnc*1000));
  Serial.print('\t');
  Serial.print((int) (avgSpeedEnc*1000));
  Serial.print('\t');
  readIRSensors();
  speedPID(); // moving
  followLine(); // steering; print line error
}

//void avoidRoutine() {
//  delay(1000);
//  Serial.println("Avoiding obstacles");
//}

void stopRoutine() {
  setMotorSTOP();
}

void wait4setting() {
//  Serial.println("waiting for input");
//  int index;
  if (Serial.available() > 0) {
    String user_speed = Serial.readStringUntil('\n');
//    for (int i = 0;i<user_speed.length();i++) {
//      if (user_speed[i] == '$') {
//        index = i;
//        break;
//      }
//    }
//    user_speed = user_speed.substring(index);
    Serial.print("You set a speed of: ");
    Serial.println(user_speed);
    Serial.flush();
  } /*else {
    user_speed = '';
  }*/
}
