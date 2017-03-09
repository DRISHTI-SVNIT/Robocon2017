#include "automation.h"

bool odometryEnable = false;
bool intF_flag = false, intB_flag = false;
int desiredJunction = 0;
int lastJunction = 0;
bool prevForward = true;
bool forward = true, reverse = false;
float HEIGHT_PARAM[7] = {63.0,15.0,25.0,72.0,25.0,15.0,69.0};

void resetAutomation() {
	odometryEnable = false;
	intF_flag = false;
	intB_flag = false;
	desiredJunction = 0;
	lastJunction = 0;
	prevForward = true;
	forward = true;
	reverse = false;
}

//Map velocity according to percent path
float velocityMap(void) {
	float velocity = 0;
	int percentPath = desiredJunction - lastJunction;
	switch((int)std::abs(percentPath)) {
		case 0:
			velocity = 0;
			odometryEnable = true;			
			break;
		case 1:
			velocity = maxVelocity * 0.1;
			odometryEnable = false;			
			break;
		case 2:
			velocity = maxVelocity;
			odometryEnable = false;			
			break;
		case 3:
			velocity = maxVelocity;
			odometryEnable = false;			
			break;
		case 4:
			velocity = maxVelocity;
			odometryEnable = false;			
			break;
		case 5:
			velocity = maxVelocity;
			odometryEnable = false;			
			break;
	}
//	if(odometryEnable == false) {
		if(percentPath < 0) {
			velocity = -velocity;
		}
		return velocity;
//	} else {
//		float curr_y = getY(getDistTravelled());
//		float error = arenaJunction[desiredJunction-1] - curr_y;
//		return PID(error,odometryControl);
//	}
}

void dir_log(float velocity){
	prevForward = forward;	
	if(velocity < 0){
		forward = false;
		reverse = true;
	} else if(velocity > 0){
		forward = true;
		reverse = false;	
	}
	if(forward == true && prevForward == false) {
		intF_flag = false;
	} else if (reverse == true && prevForward == true) {
		intB_flag = false;
	}
}






