/*
Nate Winneg
RoboRival  
    
*/

/* Includes -------------------------------------------------------*/
#include "PID_Params.h"

/* Macros ---------------------------------------------------------*/
//float setpointSpeed;
float setPointSpeed;
float setpointPWM;

float prevSpeedError;
float integralSpeedError;

//float kp_speed = 1; float ki_speed = 1; float kd_speed = 1;
/* Functions ------------------------------------------------------*/

void computeSpeed(void)
{
  /* This should take in whatever commands are given from the 
   * UI about distance and pace and compute a desired speed setpoint
   * 
   * This should also be able to be used to recalculate based on 
   * amount of distance left and time to target pace.
   */
}

float speedPID(void)
{
  float error = setpointSpeed - currSpeedEnc;
  float d_error = (error - prevSpeedError)/*/dT*/; /* dT TBD */
  integralSpeedError = integralSpeedError + error;

  float cmd = (kp_speed * error) + (ki_speed * integralSpeedError) + (kd_speed * d_error);
//  float cmd = (kp_speed * error) + (kd_speed * d_error);
  prevSpeedError = error;

  /*
   * Here cmd could just be setpointPWM if gains are set correctly
   * but we'll want to do something to cap acceleration in here
   * as well so we don't pull too much current.
   */
   return cmd;
}
