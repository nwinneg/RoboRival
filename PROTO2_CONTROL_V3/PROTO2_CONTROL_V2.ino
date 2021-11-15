using namespace std;

//#define startTime 0

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
unsigned long runTime;
event_type event = NONE;

#define ENCA_RL   18
#define ENCA_RR   19
#define ENCB_RL   50
#define ENCB_RR   51

// wheel physical params
float wheelRad = 0.05461; //4.3"

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


//float startTime;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  setupServo();
  setupMotors();
//  setupEncoders();
  pinMode(A0, INPUT);
  setupEncoders();
} 

void loop() {
  // put your main code here, to run repeatedly:
  currentTime = millis();
  readEncoders();
  if (analogRead(A0) > 1000){
    static unsigned long startTime = currentTime;
    if (currentTime - startTime < 1000) {
      setMotorSTOP();
    }
    else if (currentTime - startTime > 1000 && currentTime - startTime < 3000) {
      setMotorPWM_All(30);
    }
    else if (currentTime - startTime > 3000 && currentTime - startTime < 6000) {
      float new_cmd = speedPID();
      Serial.println(new_cmd);
      setMotorPWM_All(30 + int(2*new_cmd));
    }
    else if (currentTime - startTime > 6000) {
      setMotorSTOP();
    }
  }
}


///////////////////////
//void steering_TEST() {
//  // put your main code here, to run repeatedly:
//  currentTime = millis();
//  if (analogRead(A0) > 1000){
//    static unsigned long startTime = currentTime;
//    if (currentTime - startTime < 1000) {
//      setMotorPWM_All(0);
//    }
//    else if (currentTime - startTime > 1000 && currentTime - startTime < 4000) {
//      Serial.print("Forward\n");
//      setMotorPWM_All(35);
//      moveServo(82);
//    }
//    else if (currentTime - startTime > 4000 && currentTime - startTime < 5000) {
//      Serial.print("Left\n");
//      moveServo(92);
//    }
//    else if (currentTime - startTime > 5000 && currentTime - startTime < 6000) {
//      Serial.print("Center\n");
//      moveServo(82);
//    }
//    else if (currentTime - startTime > 6000 && currentTime - startTime < 7000) {
//      Serial.print("Right\n");
//      moveServo(72);
//    }
//    else if (currentTime - startTime > 7000 && currentTime - startTime < 8000) {
//      Serial.print("Center\n");
//      moveServo(82);
//    }
//    else if (currentTime - startTime > 5000) {
//      Serial.print("Stop\n");
//      //Serial.print("\t Power Cut!");
//      setMotorPWM_All(0);
//    }
//  }
//}
//
//void encoders_TEST() {
//  currentTime = millis();
//  readEncoders();
//  Serial.print(currDistanceEnc);
//  Serial.print("\t");
//  Serial.println(currSpeedEnc);
//  if (analogRead(A0) > 1000){
//    static unsigned long startTime = currentTime;
//    if (currentTime - startTime < 1000) {
//      setMotorPWM_All(0);
//    }
//    else if (currentTime - startTime > 1000 && currentTime - startTime < 4000) {
//      setMotorPWM_All(35);
//    }
//    else if (currentTime - startTime > 5000) {
//      setMotorPWM_All(0);
//    }
//}
//
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
