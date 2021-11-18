using namespace std;

#include "IR.h"
#include "Encoders.h"
#include "PID_Params.h"

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
#define TIMESTEP  10 // 10 ms --> 100Hz --- might need to go to 50ms for 20Hz
#define SPEED_INTERVAL  100   // 100ms for 10Hz speed PID interval
static unsigned long lastTime = 0;
static unsigned long lastTimeSpeed = 0;
unsigned long currentTime;
unsigned long runTime;
unsigned long raceStartTime;
event_type event = NONE;

//float startTime;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  setupMotors();
  setupEncoders();
  pinMode(A0, INPUT);
  setupEncoders();
  setupIR();
  setupServo();
} 

/* PUT SWITCH ON A0 OR OTHER PIN FOR STARTUP PROCEDURE */
void loop() {  
  if (analogRead(A0) > 1000) {
    currentTime = millis();
    if ((currentTime - lastTime)>=TIMESTEP)
    {
      readEncoders();
      readIRSensors();
      followLine();
      if ((currentTime - lastTimeSpeed) >= SPEED_INTERVAL) {
        motorCmd = speedPID();
        setMotorPWM_All(motorCmd);
      }
      lastTime = currentTime;
      lastTimeSpeed = currentTime;
    }
    Serial.print("Line Pos: ");
    Serial.print(linePosition);
    Serial.print("\t");
    Serial.print("PWM Cmd: ");
    Serial.print(motorCmd);
    Serial.print("\t");
    Serial.print("Speed: ");
    Serial.print(currSpeedEnc);
    Serial.print("\t");
    Serial.print("Distance: ");
    Serial.print(currDistanceEnc);
    Serial.print("\n");
  }
}
