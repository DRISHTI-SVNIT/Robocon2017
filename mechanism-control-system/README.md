Mechanism Control System
========================
Coded on TIVA TM4C123GH6PM for Robocon 2017

This version consists of control for,
 	1. Throwing mechanism.
	2. Angle changing mechanism.

How to use it
=============
1. You will need Tiva board with LLCs at peripheral pins (use Tiva LLC shield board, 2 motor drivers and shooting mechanism assembly [2 motors and 2 encoders (angle motor/encoder and throwing motor/encoder)].
2. Plug the motor output in the motor driver output and connect the 12volt power supply to the motor driver and 5volt to the input of Tiva LLC Shield.
3. Open "userLib/common.h" to find the pins to be connected with encoders and motor drivers.
4. You can test the readings and connections by running motor and observing the encoder ticks on XCTU (i.e. clockwise throwing motor rotation, generating positive ticks AND upward angle increase by motor rotation, generating positive ticks)
5. Connect the Raspberry Pi's TX pin from USB-TTL (connected on USB port of Pi) to PE4 (UART5 RX) on Tiva board.
6. Using Code Composer Studio, burn the this project on Tiva board. Run the upper-control-system code on RPi and use the buttons on PS2 to control the mechanisms.

Common troubleshooting
======================

1. UART not working?
	You can test the UART from RPi to be working or not by directly plugging in XBee shield and looking on the XCTU on your PC. On pressing "Triangle" on PS2, 128 should be displayed. If not, try replugging USB TTL on Pi and restarting the code.

2. Angle/Throwing motor does not stop rotating?
	Beware of system going havoc. Keep kill switches in proximity. In case the motor keeps moving inspite of PID application, there is a possibility of reverse phase input of encoder/motor drivers. Change either of them and check.