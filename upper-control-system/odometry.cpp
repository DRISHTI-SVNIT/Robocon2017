#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "odometry.h"
#include "encoderGrey.h"

float distance[2]={0.0,0.0};
float position[3]={0.0,0.0,0.0};
long int count[2]={0},prev[2]={0};
struct encoder *encoderA,*encoderB;

void resetOdometry(struct encoder *encoderA_,struct encoder *encoderB_) {
	writeOdometry(0,X);
	writeOdometry(0,Y);
	writeOdometry(0,Phi);
	resetEncoder(encoderA_);
	resetEncoder(encoderB_);
}

void initOdometry(struct encoder *x,struct encoder *y)
{
	encoderA=x;
	encoderB=y;		
}
float getX(float distTravelled)
{
	position[X] = position[X]+distTravelled*sin((position[Phi]));//(pi*position[Phi])/180.0);
	return position[X];
}
float getY(float distTravelled)
{
	position[Y] = position[Y]+distTravelled*cos((position[Phi]));
	return position[Y];
}
float getPhi()
{
	position[Phi] = position[Phi]+(distance[A]-distance[B])/(DistanceBetweenWheels);
	return position[Phi];
}
float getDistTravelled()
{
	distance[A]=(2*pi*RADIUSA*GetTickDiff(A))/NumberOfTicksPerRevolution1;
	distance[B]=(2*pi*RADIUSB*GetTickDiff(B))/NumberOfTicksPerRevolution2;
	return 	(distance[A]+distance[B])/2.0;
}
long int GetTickDiff(int wheel)
{
	long int tickDiff;
	if(wheel==A)
	{
		count[A]= encoderA->value;
		tickDiff= (count[A]-prev[A]);
		prev[A]=count[A];
		return tickDiff;
	}
	if(wheel==B)
	{
		count[B]=encoderB->value;
		tickDiff=(count[B]-prev[B]);
		prev[B]=count[B];
		return tickDiff;
	}
}

void writeOdometry(float Dist,int i) {
	position[i] = Dist;
}
