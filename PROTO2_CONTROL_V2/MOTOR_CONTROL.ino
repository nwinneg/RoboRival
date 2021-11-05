/*
Nate Winneg
RoboRival  
    
*/

/* Includes -------------------------------------------------------*/

/* Macros ---------------------------------------------------------*/
#define MOTORPIN_RL    4 
//#define DIRCONTROLRL   // always pulled high for now 
#define MOTORPIN_RR    5 
//#define DIRCONTROLRR   // always pulled high for now
#define MOTORPIN_FL    6 
//#define DIRCONTROLFL   // always pulled high for now 
#define MOTORPIN_FR    7 
//#define DIRCONTROLFR   // always pulled high for now 

/* Functions ------------------------------------------------------*/

void setupMotors(void)
{
  pinMode(MOTORPIN_RL, OUTPUT); pinMode(MOTORPIN_RR, OUTPUT);
  pinMode(MOTORPIN_FL, OUTPUT); pinMode(MOTORPIN_FR, OUTPUT);
}

void setMotorPWM_All(float dutyCycle)
{
  float motorSetting = (dutyCycle/100)*255;
  digitalWrite(MOTORPIN_RL, motorSetting);
  digitalWrite(MOTORPIN_RR, motorSetting);
  digitalWrite(MOTORPIN_FL, motorSetting);
  digitalWrite(MOTORPIN_FR, motorSetting);
}

void setMotorPWM_Left(float dutyCycle)
{
  float motorSetting = (dutyCycle/100)*255;
  digitalWrite(MOTORPIN_RL, motorSetting);
  digitalWrite(MOTORPIN_FL, motorSetting);
}

void setMotorPWM_Right(float dutyCycle)
{
  float motorSetting = (dutyCycle/100)*255;
  digitalWrite(MOTORPIN_RR, motorSetting);
  digitalWrite(MOTORPIN_FR, motorSetting);
}
