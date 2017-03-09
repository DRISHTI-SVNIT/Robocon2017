#include "servo.h"
#include "pwm_gen.h"
#include "init.h"
int servolibID[MAX_SERVO];
int id = -1;

void resetServo(void) {
    id = -1;
}

int servoInit(int pwmPin) {
    if(id < MAX_SERVO) {
        id++;
        servolibID[id] = pwmPin;
        return id;
    } else {
        return -1;
    }
}

void moveServo(float angle,int servo_id) {
    float degree = ((0.00186/180)*angle+0.00054);
    setServoAngle(servolibID[servo_id],degree);
}
