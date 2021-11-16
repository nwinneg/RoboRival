/*
Nate Winneg
RoboRival  
     This file defines global variables and functions related to 
     reading the rear encoders and measuring speed and distance
*/

/* Includes -------------------------------------------------------*/

/* Macros ---------------------------------------------------------*/
//#define ENCA_RL   18
//#define ENCA_RR   19
//#define ENCB_RL   50
//#define ENCB_RR   51
//
//// wheel physical params
//float wheelRad = 0.05461; //4.3"
//
//// 36.4 rises on channel A per revolution
//float encoderCountsPerRev = 36.4;
//float prevTimeEncoder = 0;
//int countsRL;
//int countsRR;
//float distRight;
//float distLeft;
//float speedLeft;
//float speedRight;
//double currDistanceEnc;
//double currSpeedEnc;

/* Functions ------------------------------------------------------*/

// we don't currently care about direction
void encoderRR(void) { countsRR++; }
void encoderRL(void) { countsRL++; }

void setupEncoders(void)
{
  pinMode(ENCA_RL, INPUT); pinMode(ENCB_RL, INPUT);
  pinMode(ENCA_RR, INPUT); pinMode(ENCB_RR, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA_RL), encoderRL, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCA_RR), encoderRR, RISING);
}

/*
 * Distance in meters
 * Speed in m/s
 */
void readEncoders2(void)
{
  
}
 
void readEncoders(void)
{
  // ms / 1000 = s
  float dT = (millis() - prevTimeEncoder)/1000;
  prevTimeEncoder = millis();
  
  // compute distance traveled during interval
  distRight = (float) 2 *PI * wheelRad * (countsRR / encoderCountsPerRev);
  distLeft = (float) 2 *PI * wheelRad * (countsRL / encoderCountsPerRev);

  
  
  // reset encoder counts for next run
  //countsRR = 0; countsRL = 0;
  
  //compute speed
  speedRight = (distRight - distRightPrev)/dT;
  speedLeft = (distLeft - distLeftPrev)/dT;

  distRightPrev = distRight;
  distLeftPrev = distLeft;
  
  //compute averaged data
  currDistanceEnc = (distLeft + distRight)/2.0;
  currSpeedEnc = (speedLeft + speedRight)/2.0;
}
