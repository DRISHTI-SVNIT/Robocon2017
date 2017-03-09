#ifndef AUTOMATION_H
#define AUTOMATION_H

#include "driveConfig.h"
#include "odometry.h"
#include <cmath>
#include "pidController.h"
#define HEIGHT_TOLERANCE 2
#define HEIGHT_ENCODER_TICKS 330.0

extern bool odometryEnable;
extern bool intF_flag, intB_flag;
extern int desiredJunction, lastJunction;
extern bool prevForward;
extern bool forward,reverse;
extern float HEIGHT_PARAM[7];

float velocityMap(void);
void dir_log(float velocity);
void resetAutomation(void);

#endif
