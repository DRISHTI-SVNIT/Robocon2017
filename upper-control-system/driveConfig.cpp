#include "driveConfig.h"

bool rotatePressed=0;
bool rotateDirection=clk;
int mode = 0;
int curMode = 0;
int preMode = 3;

void resetDriveConfig(void) {
	rotatePressed=0;
	rotateDirection=clk;
	mode = 0;
	curMode = 0;
	preMode = 3;	
}
