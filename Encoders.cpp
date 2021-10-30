/*
Nate Winneg
RoboRival  
    https://github.com/pololu/qtr-sensors-arduino
*/

/* Includes -------------------------------------------------------*/

/* Macros ---------------------------------------------------------*/

// variables to keep track of position for ea. motor
    // for now we'll only keep track of the rear motors
    """ units of meters --> 0.003048 m/count"""
double distRL = 0; 
double distRR = 0;
double distance;

// likely change these pins because PWM 2 and 3 are I2C Bus pins
    """ need to make sure ENCA pins are on interrupt compatible pins """
int ENCA_RL = 2;
int ENCA_RR = 3;
int ENCB_RL = 4;
int ENCB_RR = 5;

// timing variables to keep track of speed for each encoder
    // this method of speed calc is untested !!
double prevTimeRL = 0;
double prevTimeRR = 0;

// variables to store speed calculations
double speedRL;
double speedRR;
double speed;

/* Functions ------------------------------------------------------*/

void encodersSetup(void)
{
    pinMode(ENCA_RL, INPUT); pinMode(ENCB_RL, INPUT);
    pinMode(ENCA_RR, INPUT); pinMode(ENCB_RL, INPUT);
    
    attachInterrupt(digitalPinToInterrupt(ENCA_RL), readEncoderRL, RISING);
    attachInterrupt(digitalPinToInterrupt(ENCA_RR), readEncoderRR, RISING);
}

""" directions flipped for RL and RR speed calcs """
// probably want to make this a higher precision distance increment
void readEncoderRL(void)
{
    double currTime = millis();
    int b = digitalRead(ENCB_RL);
    if (b>0) {
        distRL += 0.003048;
    }
    else {
        distRL -= 0.003048;
    }
    speedRL = 0.003048/((currTime - prevTimeRL)*10**3); // m/s
    prevTimeRL = currTime;
}

void readEncoderRR(void)
{
    double currTime = millis();
    int b = digitalRead(ENCB_RR);
    if (b<0) {
        distRL += 0.003048;
    }
    else {
        distRL -= 0.003048;
    }
    speedRR = 0.003048/((currTime - prevTimeRR)*10**3); // m/s
    prevTimeRR = currTime;
}

// just averages for now -- no filtering
""" these variables are constantly updated on interrupt 
    run these functions to retrieve the data """
void getSpeed(void)
{
    speed = (speedRR + speedRL)/2.0;
}

void getDist(void)
{
    distance = (distRR + distRL)/2.0;
}