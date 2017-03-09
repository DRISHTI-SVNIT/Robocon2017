/*
 * angle.h
 *
 *  Created on: Dec 15, 2016
 *      Author: Aniket
 */

#ifndef ANGLE_H_
#define ANGLE_H_
#include "userLib/common.h"
#include "userLib/pidController.h"

//Angle parameter macros
#define ANGLE_TOLERANCE 			10
#define INV_WORM_GEAR_RATIO 		40.0
#define ENCODER_TICK_PER_REV 		1000.0
#define ENCODER_TICK_PER_MECH_REV	ENCODER_TICK_PER_REV*INV_WORM_GEAR_RATIO
#define TICK_PER_DEGREE				ENCODER_TICK_PER_MECH_REV/360.0
#define MAX_ANGLE                   30

//Angle change variables
extern long int angle_counter;
extern long int des_angle_counter;

void changeAngle();
void cmd_angle(int angle);
int convertPlaneAngleToTicks(float angle);

#endif /* ANGLE_H_ */
