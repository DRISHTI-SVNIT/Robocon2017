/*
 * HWtest.c
 *
 *  Created on: Oct 5, 2016
 *      Author: Aniket
 *      This source file contains functions to use for testing the hardware connections of the differential drive on Tiva boards.
 *      Run the functions one by one keeping the main with nothing except this function. (not while loop) You can comment out the codes from main.
 *         "SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
			uart0Init();
			maxPWM = SysCtlClockGet()/(PWMfrequency*64);" DO NOT COMMENT THESE STARTING THREE LINES OF MAIN
 *
 *      Change the pins as per required or change the macro configurations from "init.h" file in "userLib" folder.
 *      Once the directions and polarities and connections are checked, proceed with the tuning using the actual main.c
 */

#include "HWtest.h"

/*
 * Testing motor directions and PWM pins
 * Use the following functions to check for directions and PWM of motors.
 * Normally, positive PWM should drive motors in clockwise direction. Change pins or macro definition in "init.h" if necessary.
 */

/*
 * param :
 *  motor 	: A or B ( e.g. testMotor(A,30); )
 * 	PWM 	: Integer between 0 to maxPWM, suggested to put value maxPWM/2
 * */
void testMotor(int motor,int PWM) {
	motorDirInit();
	pwmInit();
	setPWM(PWM,motor);
}

/*
 * param :
 *  PWM_a 	: Integer between 0 to maxPWM, suggested to put value maxPWM/2
 *  PWM_b 	: Integer between 0 to maxPWM, suggested to put value maxPWM/2
 * */
void testBothMotor(int PWM_a,int PWM_b) {
	motorDirInit();
	pwmInit();
	setPWM(PWM_a,A);
	setPWM(PWM_b,B);
}

/*
 * Encoder tests
 * Use the following functions to check for directions and readings of encoders.
 * Normally, positive PWM (clockwise rotation) should give positive RPM values. Change pins or macro definition in "init.h" if necessary.
 * */

/*
 * param :
 *  encoder 	: A or B ( e.g. testEncoder(A); )
 * */

void testEncoder(int encoder, int rpm) {
	testMotor(encoder,rpm);
	qeiInit();
	IntMasterEnable();
}

void testBothEncoder(int rpmA,int rpmB) {
	testBothMotor(rpmA,rpmB);
	qeiInit();
	IntMasterEnable();
}

/* You can check the encoders without switching on motors by rotating through hands and watching the graphs plotted in while loop in "SimPlot"*/
