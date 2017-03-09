/*
 * automation.h
 *
 *  Created on: 16-Jan-2017
 *      Author: HP
 */

#ifndef AUTOMATION_H_
#define AUTOMATION_H_

#include "shoot.h"
#include "angle.h"
#include "load.h"
#include "userLib/common.h"
/*RED*/
#define POLE1_des_counter   98.706
#define POLE2_des_counter   109.13
#define POLE3_des_counter   112.423
#define POLE4_des_counter   112.941
#define POLE5_des_counter   112.423
#define POLE6_des_counter   109.13
#define POLE7_des_counter   113.651

#define POLE1_ANGLE         20
#define POLE2_ANGLE         19
#define POLE3_ANGLE         18
#define POLE4_ANGLE         20    //17-18
#define POLE5_ANGLE         18
#define POLE6_ANGLE         19
#define POLE7_ANGLE         19

#define POLE1_SHOOT_PER     0.3125
#define POLE2_SHOOT_PER     0.4475
#define POLE3_SHOOT_PER     0.5175
#define POLE4_SHOOT_PER     0.49      //58-63
#define POLE5_SHOOT_PER     0.5175
#define POLE6_SHOOT_PER     0.4475
#define POLE7_SHOOT_PER     0.7025

/*BLUE*/
/*#define POLE1_des_counter   284.146
#define POLE2_des_counter   294.13
#define POLE3_des_counter   297.423
#define POLE4_des_counter   295.941
#define POLE5_des_counter   297.423
#define POLE6_des_counter   294.13
#define POLE7_des_counter   291.8

#define POLE1_ANGLE         8
#define POLE2_ANGLE         18
#define POLE3_ANGLE         18
#define POLE4_ANGLE         21    //17-18
#define POLE5_ANGLE         18
#define POLE6_ANGLE         18
#define POLE7_ANGLE         20

#define POLE1_SHOOT_PER     0.338
#define POLE2_SHOOT_PER     0.4925
#define POLE3_SHOOT_PER     0.5674
#define POLE4_SHOOT_PER     0.5274      //58-63
#define POLE5_SHOOT_PER     0.4975
#define POLE6_SHOOT_PER     0.5674
#define POLE7_SHOOT_PER     0.725
*/
struct set_parameters {
    float SHOOT_PERCENT;
    int PLANE_ANGLE;
    float THROW_ANGLE;
};

typedef struct set_parameters SET_VALUE;
SET_VALUE SET_PARAMETERS(int POLE);

#endif /* AUTOMATION_H_ */
