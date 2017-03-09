#ifndef ODOMETRY_H
#define ODOMETRY_H
#include "encoderGrey.h"
#include "driveConfig.h"

#define DistanceBetweenWheels L
#define RADIUSA wheelRadius
#define RADIUSB wheelRadius
#define pi 3.14159
#define NumberOfTicksPerRevolution1 705.0
#define NumberOfTicksPerRevolution2 700.0

enum{X,Y,Phi};
enum{A,B};

void resetOdometry(struct encoder *encoderA_,struct encoder *encoderB_);
float getX(float DC);
float getY(float DC);
float getPhi();
float getDistTravelled();
long int GetTickDiff(int i);
void writeOdometry(float Dist,int i);
void initOdometry(struct encoder *x,struct encoder *y);

#endif 
