/* Includes -------------------------------------------------------*/
#include <QTRSensors.h>
/* Macros ---------------------------------------------------------*/
#define EVEN_EMITTER_PIN 14
#define ODD_EMITTER_PIN 15
#define NUM_SENSORS 26//13
//#define TIMEOUT 2000 // amount of time after which reading is 0

QTRSensors qtr;
QTRReadMode ReadMode = QTRReadMode::On;

uint16_t sensorValues[NUM_SENSORS]; // set up array for read() method

unsigned long previousMicros = 0;

uint16_t linePosition;
uint16_t prevLinePosition;

float kp_line = 0.38, kd_line = 0;
float lineRef = 125, lineRefDot = 0;

float turningAngle = 84; // SERVO_HOME
