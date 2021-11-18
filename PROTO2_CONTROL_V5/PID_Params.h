#ifndef PID
#define PID


/* Parameteres for Speed PID */
float setpointSpeed = 0.5;
float kp_speed = 1; float ki_speed = 1; float kd_speed = 1;

/* Parameters for Line Following PID */
float kp_line = 0.3, kd_line = 0;
float lineRef = 125, lineRefDot = 0;

/* Motor PWM Cmd for tracking purposes */
float motorCmd;

#endif
