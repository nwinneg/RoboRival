using namespace std;

#define startTime 0

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

bool TEST = true;
static unsigned long lastTime = 0;
unsigned long currentTime;
event_type event;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  setupServo();
  setupMotors();
//  setupEncoders();
} 

void loop() {
  // put your main code here, to run repeatedly:
  
  if (TEST) {
    currentTime = millis(); //tracking time
    if (currentTime < 5000) {
      event = UI_START; // start with UI_START
    }
    if (currentTime > 5000 && currentTime < 10000) {
      event = TIMER_ENDS; // after 5 sec, TIMER_ENDS becomes the event
    }
    if (currentTime > 10000) {
      event = ESTOP; // after 10 sec, ESTOP becomes the event
    }
    roborival_FSM(event);
  }
  event = NONE; // reset event
}
