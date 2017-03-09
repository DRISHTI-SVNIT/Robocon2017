#ifndef SERVO_H
#define SERVO_H

#define MAX_SERVO 2

void resetServo(void);
int servoInit(int pwmPin);
void moveServo(float angle,int servo_id);

#endif
