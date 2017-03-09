#ifndef LOAD_H
#define LOAD_H

#include "userLib/common.h"
#include "userLib/servo.h"

#define LIMIT_ENABLE	0
#define SERVO_ANGLE1	30.0
#define SERVO_ANGLE2	150.0
#define SERVO_DELAY		20000000
enum {up, down};

extern volatile int8_t start_color,transition_color;
extern volatile uint8_t reload_in_progress;
extern volatile uint8_t no_of_discs_loaded[2];
extern volatile uint8_t system_going_0_from_top;
extern bool loadEnable;
void resetLoad(void);
void loadInit(void);
int8_t reload(uint8_t loaderID);
void reload_manual(uint8_t mech_no, uint8_t dir);
int8_t moveLoader(uint8_t i,uint8_t startColor,uint8_t dir);
void checkForSafetyTrigger(uint8_t mech_no,uint8_t dir);
int IRstateConfidenceCheck(uint8_t mech_no);
void bring_system_to_0_from_top(uint8_t mech_no);
void bring_system_to_0_from_bottom(uint8_t mech_no);

#endif
