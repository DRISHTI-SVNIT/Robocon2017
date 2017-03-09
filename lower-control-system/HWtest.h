/*
 * HWtest.h
 *
 *  Created on: Oct 5, 2016
 *      Author: Aniket
 */

#ifndef HWTEST_H_
#define HWTEST_H_

#include "userLib/common.h"
#include "userLib/init.h"
#include "userLib/pidController.h"
#include "userLib/movingArray.h"

void testMotor(int motor, int PWM);
void testBothMotor(int PWM_a, int PWM_b);
void testEncoder(int encoder,int rpm);
void testBothEncoder(int rpmA,int rpmB);

#endif /* HWTEST_H_ */
