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
          Serial.print("Entered UI_START\n");
          nextState = COUNTDOWN;
          calibRoutine(); // hidden action
          countdRoutine(); // actual action
        default:
          Serial.print("STUCK\n");
          nextState = currentState;
      }
      break;
    case COUNTDOWN:
      switch (newEvent) {
        case TIMER_ENDS:
          Serial.print("Entered TIMER_ENDS\n");
          nextState = DRIVING_STRAIGHT;
          forwardRoutine(); // a routine that includes driving motors and tracking lines
        default:
          Serial.print("Entered COUNTDOWN\n");
          nextState = currentState;
      }
      break; 
    
    case DRIVING_STRAIGHT:
      switch (newEvent) {
        case OBS_DETECTED:
          nextState = AVOIDING_OBSTACLE;
          avoidRoutine();
        case IMPACT_DETECTED:
          nextState = STOPPING;
          stopRoutine();
        case ESTOP:
          nextState = STOPPING;
          stopRoutine();
        case RACE_COMPLETED:
          nextState = STOPPING;
          stopRoutine();
//        case TURN_DETECTED:
//          nextState = DRIVING_CORNER;
//          stopRoutine();
        default:
          nextState = currentState;
      }
      break;
      
//    case DRIVING_CORNER:
//    break;
    
    case AVOIDING_OBSTACLE:
      switch (newEvent) {
        case OBS_CLEARED:
          nextState = DRIVING_STRAIGHT;
          forwardRoutine();
        default:
          nextState = currentState;
      }
      break;
    
    case STOPPING:
      switch (newEvent) {
        case STOPPED:
          nextState = WAITING;
        default:
          nextState = currentState;
      }
      break;
  }
  currentState = nextState;
}

void calibRoutine() {
  delay(1000); // only for testing
  Serial.print("Calibrating\n");
}

void countdRoutine() {
  delay(1000);
  Serial.print("Countdown\n");
}

void forwardRoutine() {
  Serial.print("Going forward\n");
  float spd = 10; // only for testing
  int duration = 2000; // only for testing
  setMotorPWM_All(spd);
  delay(duration);
  setMotorPWM_All(0);
}

void avoidRoutine() {
  delay(1000);
  Serial.print("Avoiding obstacles\n");
}

void stopRoutine() {
  delay(1000);
  Serial.print("Stopping\n");
}
