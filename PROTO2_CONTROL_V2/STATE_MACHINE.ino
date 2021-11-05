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
  DRIVING_CORNER,
  AVOIDING_OBSTACLE,
  STOPPING
} robot_state;

typedef enum
{
  // list out the events that can trigger things here
}event_types;

/* Functions ------------------------------------------------------*/

void stateMachineFunction (event_type new_event)
{
  switch (state)
  {
    case WAITING:
      // STUFF
    break;
    case COUNTDOWN:
      // STUFF
    break; 
    case DRIVING_STRAIGHT:
      // STUFF
    break;
    case DRIVING_CORNER:
      // STUFF
    break;
    case AVOIDING_OBSTACLE:
      // STUFF
    break;
    case STOPPING:
      // STUFF
    break;
  }
}
