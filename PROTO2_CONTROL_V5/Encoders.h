#define ENCA_RL   18
#define ENCA_RR   19
#define ENCB_RL   50
#define ENCB_RR   51

// wheel physical params
float wheelRad = 0.05461;// 4.3" -- error with squishiness

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