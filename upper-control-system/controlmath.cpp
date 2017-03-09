#include "controlmath.h"
#include <math.h>
#include "pidController.h"
#include <stdio.h>

float sigmoid(float x) {
	return ((1/(1+exp(-x))) - 0.5) * 2;
}

float degreeToRadian(float degree) {
    return degree * PI / 180;
}

float radianToDegree(float radian) {
    return radian * 180 / PI;
}

float normalizeAngle(float degree) {
    return radianToDegree(atan2(sin(degreeToRadian(degree)), cos(degreeToRadian(degree))));
}

struct point rotationalTransform(struct point point_, float theta) {
	return rotationalTransform(point_.x, point_.y, theta);
}

float majorAngleFilter(float err) {
	if(err>0) {
		if(err<=180) {
			return err;
		}
		else {
			return err-360;
		}
	} else {
		if(err>=-180) {
			return err;
		}
		else {
			return err+360;
		}
	}
}

struct point rotationalTransform(float x, float y, float theta){
    struct point pos;
    theta = degreeToRadian(theta);
    pos.x = x * cos(theta) + y * sin(theta);
    pos.y = y * cos(theta) - x * sin(theta);
    return pos;
}

struct differentialState rpmLimiter(struct differentialState state) {
	float max,factor = 1,dividend = 1;
	(fabs(state.leftRPM) >= fabs(state.rightRPM)) ? max = fabs(state.leftRPM) : max = fabs(state.rightRPM);
	dividend = max;
	if(max > maxRPM) {
		while(dividend > maxRPM) {
			dividend = max / factor;
			factor += 0.1;
		}
		factor -= 0.1;
		state.leftRPM /= factor;	
		state.rightRPM /= factor;	
		return state;
	}
	return state;
}

struct unicycleState velocityLimiter(struct unicycleState state) {
	float max,factor = 1,dividend = 1;
	(fabs(state.vx) >= fabs(state.vy)) ? max = fabs(state.vx) : max = fabs(state.vy);
	dividend = max;
	if(max > maxVelocity) {
		while(dividend > maxVelocity) {
			dividend = max / factor;
			factor += 0.5;
		}
		factor -= 0.5;
		state.vx /= factor;	
		state.vy /= factor;	
	}
	return state;
}

struct differentialState transformUniToDiff(struct unicycleState uniState) {
	struct differentialState diffState;
   	float v = sqrt(uniState.vx * uniState.vx + uniState.vy * uniState.vy);
	float w = fabs((L*uniState.w * 60.0) / (4 * wheelRadius * PI));	
	if(uniState.vy<0) {
		v = -v;
	}
	//using the kinematics equations
	float vleft = (2*v - L*uniState.w) / (2 * wheelRadius);
	float vright = (2*v + L*uniState.w)/(2 * wheelRadius);
	diffState.rightRPM = (vright * 60.0) / (2.0 * PI);
	diffState.leftRPM = (vleft * 60.0) / (2.0 * PI);
	return rpmLimiter(diffState);
}






