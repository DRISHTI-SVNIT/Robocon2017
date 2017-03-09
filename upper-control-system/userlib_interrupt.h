#ifndef userlib_interrupt
#define userlib_interrupt
#include "driveConfig.h"
#include <wiringPi.h>
#include <unistd.h>
#include <stdio.h>
#include "ps2USB.h"
#include "minimu9.h"
#include "timerInterrupt.h"

extern void slowTimerHandler();
extern void ps2Activated();
extern void ps2Deactivated();
extern void imuActivated();
extern void imuDeactivated();

void slowTimerHandler() {
	printf("slowLoop\n");
}

void powerOff() {
}

void ps2Activated() {
	printf("ps2 Activated...\n");
	ps2Ready = true;
}

void ps2Deactivated() {
	printf("PS2 Deactivated...\n");
	ps2Ready = false;
}

void imuActivated() {
	printf("IMU Activated...\n");
	imuReady = true;
}

void imuDeactivated() {
	printf("IMU Deactivated...\n");
	imuReady = false;
}

#endif
