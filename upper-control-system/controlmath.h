#ifndef controlmath
#define controlmath

#define PI 3.1415926
#include "driveConfig.h"

struct point { float x; float y; };
struct unicycleState {float vx; float vy; float w;};	// Preference of vx and vy because sending only v will require to send phi information explicitly while
														// vx and vy implicitly define phi as well as v. In a nutshell, easily understandable. You can delete these
														// these comments when understood about the changes
struct position {float x; float y; int phi;};


float sigmoid(float x);
float degreeToRadian(float degree);
float radianToDegree(float radian);
float normalizeAngle(float degree);
float majorAngleFilter(float err);
struct point rotationalTransform(struct point point_, float theta);
struct point rotationalTransform(float x_, float y_, float theta);
struct differentialState transformUniToDiff(struct unicycleState unistate); //alpha is the angular offset given to the robot
struct unicycleState getDesiredUnicycleState( struct position curBotPosition, struct position desiredBotPosition) ;

#endif
