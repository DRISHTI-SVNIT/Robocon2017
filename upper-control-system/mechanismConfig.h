#ifndef MECHANISM_CONFIG_H
#define MECHANISM_CONFIG_H

#include "ps2_2k17.h"
#define USBTTLPORT "/dev/rfcomm1"

extern int printer_shoot,printer_load,printer_planeAngle,printer_dataFrame;

void initMechanism();
void endMechanism();
bool transmitMechanismPacket(int pole);
bool transmitMechanismPacket(int throw_, int load_, int planeAngle_, int rpmChange_, int posChange_);

#endif
