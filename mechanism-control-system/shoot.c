/*
 * shoot.c
 *
 *  Created on: Dec 15, 2016
 *      Author: Aniket
 */
#define LOADING 1
#include "shoot.h"
#include <math.h>

int shootComplete = 1,triggered = 0;
long int des_throw_counter = STEP, FIRST_STAGE = STEP/THROW_REVOLUTION, SECOND_STAGE = STEP/THROW_REVOLUTION * 1;
volatile long int throw_counter = STEP;
unsigned int steady_state_counter = 0;
bool steady = false;
float throw_angle = 0;
long int loadPointHolder = 0;
bool shootEnable = false;

void updateFirstStage(void) {
    FIRST_STAGE = des_throw_counter - STEP + STEP/THROW_REVOLUTION;
}

void updateDesiredStage(void) {
    des_throw_counter = throw_counter;
    throw_angle = convertTicksToThrowAngle(throw_counter);
}

long int loadPoint(void) {
	int factor = round(des_throw_counter / TICK_PER_REV);
	return TICK_PER_REV*factor;
}

int8_t moveThrower(long int desiredCount) {
	float error = (desiredCount-throw_counter);
	float pwm = PID(throw_motor,error);
	if(absolute(error)<=SHOOT_TOLERANCE)
	{
		setPWM(0,throw_motor);
		if(steady == false) {
			steady_state_counter++;
		}
		if(steady_state_counter > STEADY_STATE_CONFIDENCE) {
			steady = true;
			return 1;
		}
	} else {
	    steady = false;
		steady_state_counter = 0;
		setPWM(pwm,throw_motor);
	}
	return 0;
}

void shootDisc(bool shootState) {
    if(shootState == true) {
        if(throw_counter <= FIRST_STAGE && shootEnable == true) {
            shootComplete = 0;
            setPWM(maxPWM_throw,throw_motor);
        }
        else if(throw_counter>FIRST_STAGE && throw_counter<=(FIRST_STAGE  + SECOND_STAGE) && shootEnable == true) {
            shootComplete = 0;
            setPWM(minPWM_throw,throw_motor);
        } else {
            shootEnable = false;
#if LOADING == 0
            shootComplete = moveThrower(des_throw_counter);
#else
            if(currLoaderID == loader1) {
                shootComplete = moveThrower(loadPointHolder - LOAD_ANGLE_COUNTER1 + TICK_PER_REV);
            } else if(currLoaderID == loader2) {
                shootComplete = moveThrower(loadPointHolder + LOAD_ANGLE_COUNTER2);
            }
#endif
            if(shootComplete == true) {
                loadComplete = false;
            }
        }
    } else {
        if(loadComplete == true) {
            moveThrower(des_throw_counter);
        } else {
#if LOADING == 1
            if(currLoaderID == loader1) {
                moveThrower(loadPointHolder - LOAD_ANGLE_COUNTER1 + TICK_PER_REV);
            } else if(currLoaderID == loader2) {
                moveThrower(loadPointHolder + LOAD_ANGLE_COUNTER2);
            }
#else
            moveThrower(des_throw_counter);
#endif
        }
    }
}

void cmd_throw(void) {
	if((des_throw_counter + STEP) < 0)
	{
		throw_counter = throw_counter - des_throw_counter + STEP;
	}
	des_throw_counter += STEP;
	FIRST_STAGE += STEP;
	if(des_throw_counter < 0) {             //Handling variable overflow
		des_throw_counter = STEP;
		FIRST_STAGE = des_throw_counter/THROW_REVOLUTION;
	}
    steady_state_counter = 0;
    loadPointHolder = loadPoint();
    shootEnable = true;
}
float convertTicksToThrowAngle (long int count){
    float angle;
    int rev;
    rev = (count/TICK_PER_REV);
    count = count - (rev*TICK_PER_REV);
    angle = (float)(count/TICKS_PER_REVOLUTION_PER_DEGREE);
    return angle;
}

long int convertThrowAngleToTicks(float angle){
    int rev;
    rev = (throw_counter/TICK_PER_REV);
    long int count = angle * TICKS_PER_REVOLUTION_PER_DEGREE;
    count = (rev*TICK_PER_REV) + count;
    return count;
}
