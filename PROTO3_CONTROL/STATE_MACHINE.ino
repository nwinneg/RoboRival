/*
Nate Winneg
RoboRival  
    https://github.com/pololu/qtr-sensors-arduino
*/

/* Includes -------------------------------------------------------*/

/* Macros ---------------------------------------------------------*/

typedef enum
{
  WAITING,
  COUNTDOWN,
  DRIVING_STRAIGHT,
//  DRIVING_CORNER,
  AVOIDING_OBSTACLE,
  STOPPING
} robot_state;

// event_type is commented to prevent double declaration
//typedef enum 
//{
//  // list out the events that can trigger things here
//  UI_START,
//  TIMER_ENDS,
//  OBS_DETECTED,
//  IMPACT_DETECTED,
//  ESTOP,
//  RACE_COMPLETED,
////  TURN_DETECTED,
//  OBS_CLEARED,
//  STOPPED,
//  NONE
//} event_type;

/* Functions ------------------------------------------------------*/

void roborival_FSM (event_type newEvent) {
  static robot_state currentState = WAITING;
  robot_state nextState;
  
  switch (currentState)
  {
    case WAITING:
      switch (newEvent) {
        case UI_START:
          Serial.print("Event UI_START\n");
          nextState = COUNTDOWN;
          calibRoutine(); // hidden action
          countdRoutine(); // actual action
          break;
        default:
          Serial.print("ENTERED WAITING State\n");
          nextState = currentState;
          break;
      }
      break;
    case COUNTDOWN:
      switch (newEvent) {
        case TIMER_ENDS:
          Serial.print("Event TIMER_ENDS\n");
          nextState = DRIVING_STRAIGHT;
          forwardRoutine(); // a routine that includes driving motors and tracking lines
          break;
        default:
          Serial.print("Entered COUNTDOWN State\n");
          nextState = currentState;
          break;
      }
      break; 
    
    case DRIVING_STRAIGHT:
      switch (newEvent) {
        case OBS_DETECTED:
          nextState = AVOIDING_OBSTACLE;
          avoidRoutine();
          break;
        case IMPACT_DETECTED:
          nextState = STOPPING;
          stopRoutine();
          break;
        case ESTOP:
          Serial.print("Event ESTOP\n");
          nextState = STOPPING;
          stopRoutine();
          break;
        case RACE_COMPLETED:
          nextState = STOPPING;
          stopRoutine();
          break;
//        case TURN_DETECTED:
//          nextState = DRIVING_CORNER;
//          stopRoutine();
//          break;
        default:
          Serial.print("Entered DRIVING_STRAIGHT State\n");
          nextState = currentState;
          break;
      }
      break;
      
//    case DRIVING_CORNER:
//    break;
    
    case AVOIDING_OBSTACLE:
      switch (newEvent) {
        case OBS_CLEARED:
          nextState = DRIVING_STRAIGHT;
          forwardRoutine();
          break;
        case ESTOP:
          Serial.print("Event ESTOP\n");
          nextState = STOPPING;
          stopRoutine();
          break;
        default:
          nextState = currentState;
      }
      break;
    
    case STOPPING:
      switch (newEvent) {
        case STOPPED:
          Serial.print("Event STOPPED\n");
          nextState = WAITING;
          break;
        default:
          Serial.print("Entered STOPPING State\n");
          nextState = currentState;
          break;
      }
      break;
  }
  currentState = nextState;
}

void calibRoutine() {
  Serial.println("Start calibrating");
  setupIR();
  setupServo();
  Serial.println("Calibrated");
}

void countdRoutine() {
  delay(1000);
  Serial.print("Countdown\n");
}

void forwardRoutine() {
//  Serial.print("Going forward\n");
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
  followLine();
}

void avoidRoutine() {
  delay(1000);
  Serial.print("Avoiding obstacles\n");
}

void stopRoutine() {
  setMotorSTOP();
}
