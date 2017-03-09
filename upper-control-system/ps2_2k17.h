#ifndef ps2_2k17
#define ps2_2k17

/*
* This header consists of the PS2 configuration for Robocon 2017
* The key mapping is as follows :
	Triangle:
		    * Mode 0 : Shoot enable *
	Cross:
		    * Mode 0 : Load enable*
	Circle:
		    * Mode 0 : Increase plane angle *
		+R1 * Mode 0 : Decrease plane angle *
	Square:
		    * Mode 0 : Increase thrower position *
		+R1 * Mode 0 : Decrease thrower position *
	R2 functions :
		    * Mode 0 : Increase RPM *
		+R1 * Mode 0 : Decrease RPM *
*/


#include "driveConfig.h"

extern void transmitDiffState(struct differentialState desiredDiffState);
extern void (*circlePressed)(void);
extern void (*circleReleased)(void);
extern void (*squarePressed)(void);
extern void (*squareReleased)(void);
extern void (*crossPressed)(void);
extern void (*crossReleased)(void);
extern void (*trianglePressed)(void);
extern void (*triangleReleased)(void);
extern void (*L1Pressed)(void);
extern void (*L1Released)(void);
extern void (*L2Pressed)(void);
extern void (*L2Released)(void);
extern void (*L3Pressed)(void);
extern void (*L3Released)(void);
extern void (*R1Pressed)(void);
extern void (*R1Released)(void);
extern void (*R2Pressed)(void);
extern void (*R2Released)(void);
extern void (*R3Pressed)(void);
extern void (*R3Released)(void);
extern void (*startPressed)(void);
extern void (*startReleased)(void);
extern void (*selectPressed)(void);
extern void (*selectReleased)(void);

extern bool rotatePressed;
extern bool rotateDirection;
extern int mode;
extern int desiredJunction;
extern int lastJunction;
extern int curMode;
extern int preMode;
extern float headingOffset;
extern int shoot, load, planeAngle;
extern int junctionCount, prevJunctionCount;

enum {noChangeRPM,increaseRPM,decreaseRPM,initialRPM};
enum {noChangePos,increasePos,decreasePos,initialPos};
enum {noChangeAngle,increaseAngle,decreaseAngle,initialAngle};
enum {square_enum,circle_enum,r1_enum,r2_enum,triangle_enum,cross_enum};
enum {manual_enum,semiauto_enum,auto_enum,imu_enum,reset_enum};

int getMode(void);
void modeChange(void);
bool mechanismState();
int getMechanismMode();
int getHeightMode();
int getJunctionAutomation();
void writeJunctionAutomation(bool state);
void writeHeightMode(int i);
struct unicycleState rotateBot(void);
void initPS2_2k17(void);
struct unicycleState rotateClk(void);
struct unicycleState rotateAnticlk(void);
void resetPS2_2k17(void);
void rotateCheck(void);
void transmitMechanismControl();

#endif








