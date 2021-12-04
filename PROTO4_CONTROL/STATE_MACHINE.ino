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
//          setLEDColor(CRGB::Black);
          nextState = SETUP;
          setLEDColor(CRGB::Yellow);
//          setup_led(true);
          calibRoutine(); // 10 secs
          setLEDColor(CRGB::HotPink);
//          setup_led(false); 
          break;
        default:
          waiting_led(true);
          Serial.println("ENTERED WAITING State");
          nextState = currentState;
          break;
      }
      break;
    case SETUP:
      switch (newEvent) {
        case UI_START:
          Serial.println("Event UI_START");
          nextState = COUNTDOWN;
          setLEDColor(CRGB::Red);
          countdown_led(true);
//          setLEDColor(CRGB::Purple);
          countdRoutine();
          digitalWrite(UI_RESET, LOW);
//          for (int i = 0; i < 10; i++)
//          {
//            countdown_led(true);
//            delay(1000);
//          }
//          setLEDColor(CRGB::Orange);
          break;
        case UI_RESET:
          Serial.println("Event UI_RESET");
          nextState = WAITING;
          break;
        default:
          Serial.println("ENTERED SETUP STATE");
          nextState = currentState;
          break;
      }
      break;
    case COUNTDOWN:
      switch (newEvent) {
        case TIMER_ENDS:
          Serial.print("Event TIMER_ENDS");
//          setLEDColor(CRGB::Purple);
          nextState = DRIVING_STRAIGHT;
          countdown_led(false);
//          forwardRoutine(); // read IR sensors, follow line and read encoders
          break;
        case UI_RESET:
          Serial.println("Event UI_RESET");
          nextState = WAITING;
          break;
        default:
          Serial.print("Entered COUNTDOWN State\n");
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
          break;
        case UI_STOP:
          Serial.println("UI_STOP");
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
//          driving_led(true);
          setLEDColor(CRGB::Green);
          Serial.print("Entered DRIVING_STRAIGHT State\n");
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
  Serial.println("Going forward (reading encoders; reading IR sensors; following line)");
  readEncoders();
//  Serial.print(currentTimePi);
//  Serial.print('\t');
//  Serial.print((int) (currDistanceEnc*1000));
//  Serial.print('\t');
//  Serial.print((int) (currSpeedEnc*1000));
//  Serial.print('\t');
//  Serial.print((int) (avgSpeedEnc*1000));
//  Serial.print('\t');
  readIRSensors();
  followLine();
}

void avoidRoutine() {
  delay(1000);
  Serial.println("Avoiding obstacles");
}

void stopRoutine() {
  setMotorSTOP();
}
