#include "mechanismConfig.h"
#include <stdio.h>
#include <wiringSerial.h>
#include <fstream>
#include <istream>

int atmegaPort;

//Debugger variables
int printer_shoot = 0,printer_load = 0,printer_planeAngle = 0,printer_dataFrame = 0;

void initMechanism() {
	atmegaPort = serialOpen(USBTTLPORT,9600);
}
void endMechanism() {
	serialClose(atmegaPort);
}
bool transmitMechanismPacket(int pole) {
	if(mechanismState() == true) {
		unsigned char dataFrame = 0b11111000;
		dataFrame |= pole;
		serialPutchar(atmegaPort, dataFrame);
		printer_dataFrame = dataFrame;
	//	std::ofstream data_file;
	//	data_file.open("data.log",std::ios::app);
	//	data_file << "Mechanism status:" << dataFrame << ";\n" ;
	//	data_file.close();
		return true;
	} else {
		return false;
	}
}

bool transmitMechanismPacket(int shoot_, int load_, int planeAngle_, int rpmChange_, int posChange_) {
	if(mechanismState() == true) {
		unsigned char dataFrame = 0;
		dataFrame |= shoot_ << 7;
		dataFrame |= load_ << 6;
		dataFrame |= planeAngle_ << 4;
		dataFrame |= rpmChange_ << 2;
		dataFrame |= posChange_;
		serialPutchar(atmegaPort, dataFrame);
		printer_shoot = shoot_;
		printer_load = load_;
		printer_planeAngle = planeAngle_;
		printer_dataFrame = dataFrame;
	//	std::ofstream data_file;
	//	data_file.open("data.log",std::ios::app);
	//	data_file << "Mechanism status:" << dataFrame << ";\n" ;
	//	data_file.close();
		return true;
	} else {
		return false;
	}
}






