/*
Nate Winneg
RoboRival  
    https://github.com/pololu/qtr-sensors-arduino
*/

/* Includes -------------------------------------------------------*/

/* Macros ---------------------------------------------------------*/

/* Functions ------------------------------------------------------*/

void motorsSetup(void)
{
    pinMode(MOTORPIN_FL, OUTPUT);
    pinMode(MOTORPIN_FR, OUTPUT);
    pinMode(MOTORPIN_RL, OUTPUT);
    pinMode(MOTORPIN_RR, OUTPUT);
}

void writeMotor(motor, dutyCycle)
{
    motorCmd = (dutyCycle/100.)*255.;
    analogWrite(motor, motorCmd);
}