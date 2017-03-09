#ifndef driveConfig
#define driveConfig

/* Tolerance */
#define HEADING_TOLERANCE 2

/* GPIO pin def */
#define headingRefButton 7
#define heightMotorPin1 27
#define heightMotorPin2 28
#define heightMotorPWM 	26
#define relayButton 29

extern bool ps2Ready;
extern bool imuReady;
extern bool powerOffPressed;

extern bool rotatePressed;
extern bool rotateDirection;

extern int mode;
extern int curMode;
extern int preMode;

extern int desiredJunction;
extern int lastJunction;
extern float arenaJunction[];

enum {clk,antiClk};			//Rotate direction enum
enum {left, right}; 			//Wheel enum
enum {headingControl,lineControl_fw,lineControl_bw,heightControl,odometryControl};	//PID controller enum

struct differentialState {int leftRPM; int rightRPM;};

//Bot specifications
#define wheelRadius 				6.5 // prev value 5
#define wheelCircumference 			(2 * PI * wheelRadius)
#define L					105.5 //prrev val 96
#define wRotate 				0.75
#define distFromLS				80.0

//Motion constraints specifications
#define maxRPM			200	//in rpm
#define maxVelocity		300 //in cm/s

//Frequency specifications
#define PIDfrequency	40

void resetDriveConfig();

#endif
