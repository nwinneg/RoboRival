/*
Nate Winneg
RoboRival  
    
*/

/* Includes -------------------------------------------------------*/

/* Macros ---------------------------------------------------------*/
#define MOTORPIN_RL    2 
#define DIRCONTROLRL  50
#define MOTORPIN_RR    3 
#define DIRCONTROLRR  51
#define MOTORPIN_FL    5 
#define DIRCONTROLFL  53
#define MOTORPIN_FR    4 
#define DIRCONTROLFR  52 

/* Functions ------------------------------------------------------*/

void setupMotors(void)
{
  pinMode(MOTORPIN_RL, OUTPUT); pinMode(MOTORPIN_RR, OUTPUT);
  pinMode(MOTORPIN_FL, OUTPUT); pinMode(MOTORPIN_FR, OUTPUT);

  pinMode(DIRCONTROLRL, OUTPUT); pinMode(DIRCONTROLRR, OUTPUT);
  pinMode(DIRCONTROLFL, OUTPUT); pinMode(DIRCONTROLFR, OUTPUT);
}

// set all motors to the same speed
void setMotorPWM_All(float dutyCycle)
{
  float motorSetting = (dutyCycle/100)*255;
  analogWrite(MOTORPIN_RL, motorSetting);
  analogWrite(MOTORPIN_RR, motorSetting);
  analogWrite(MOTORPIN_FL, motorSetting);
  analogWrite(MOTORPIN_FR, motorSetting);

  digitalWrite(DIRCONTROLRL, HIGH);
  digitalWrite(DIRCONTROLRR, HIGH);
  digitalWrite(DIRCONTROLFL, HIGH);
  digitalWrite(DIRCONTROLFR, HIGH);
}


// set left motors to the same speed
void setMotorPWM_Left(float dutyCycle)
{
  float motorSetting = (dutyCycle/100)*255;
  analogWrite(MOTORPIN_RL, motorSetting);
  analogWrite(MOTORPIN_FL, motorSetting);
}

// set right motors to the same speed
void setMotorPWM_Right(float dutyCycle)
{
  float motorSetting = (dutyCycle/100)*255;
  analogWrite(MOTORPIN_RR, motorSetting);
  analogWrite(MOTORPIN_FR, motorSetting);
}

void setMotorSTOP()
{
  digitalWrite(DIRCONTROLRL, LOW);
  digitalWrite(DIRCONTROLRR, LOW);
  digitalWrite(DIRCONTROLFL, LOW);
  digitalWrite(DIRCONTROLFR, LOW);
}
