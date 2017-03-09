#ifndef common
#define common

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_uart.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/qei.h"
#include "pwm_gen.h"
#include "driverlib/eeprom.h"

enum {angle_motor,throw_motor};
enum {loader1, loader2};

extern int32_t maxPWM_angle,maxPWM_throw, minPWM_throw,minPWM_angle;

#define PIDfrequency 						100
#define PWMfrequency 						2500
#define MAX_LOAD_DISK 						100
#define LOAD_POSITION_CONFIDENCE			1000
/* Throwing macros*/
#define SYSCTLPERIPH_THROW_MOTOR		 	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA)
#define THROW_MOTOR_PORT 					GPIO_PORTA_BASE
#define TM1 								GPIO_PIN_7
#define TM2 								GPIO_PIN_6
#define TM1_MASK 							0b10000000
#define TM2_MASK 							0b01000000
#define SYSCTLPERIPH_THROW_ENC				SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF)
#define THROW_ENCODER_PORT					GPIO_PORTF_BASE
#define THROW_ENCODER_CHANNELA				GPIO_PIN_0
#define THROW_ENCODER_CHANNELB				GPIO_PIN_1
#define THROW_ENCODER_CHANNELA_PINCONFIG	GPIO_PF0_PHA0
#define THROW_ENCODER_CHANNELB_PINCONFIG	GPIO_PF1_PHB0
//PWM pin for throwing motor PE5

/* Angle change macros*/
#define SYSCTLPERIPH_ANGLE_MOTOR 			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE)
#define ANGLE_MOTOR_PORT 					GPIO_PORTE_BASE
#define AM1 								GPIO_PIN_3
#define AM2 								GPIO_PIN_2
#define AM1_MASK 							0b00001000
#define AM2_MASK 							0b00000100
#define SYSCTLPERIPH_ANGLE_ENC 				SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF)
#define ANGLE_ENCODER_PORT					GPIO_PORTF_BASE
#define ANGLE_ENCODER_CHANNELA				GPIO_PIN_3
#define ANGLE_ENCODER_CHANNELB				GPIO_PIN_2
//PWM pin for angle motor  PD0

/* Loading macros */
#define LOAD_ANGLE1                         3
#define LOAD_ANGLE2                         183
/* Loading motor definitions */
#define SYSCTLPERIPH_LOAD_MOTOR1 			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA)
#define SYSCTLPERIPH_LOAD_MOTOR2 			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC)
#define LOAD_MOTOR1_PORT 					GPIO_PORTA_BASE
#define LOAD_MOTOR2_PORT 					GPIO_PORTC_BASE
#define LM11 								GPIO_PIN_3
#define LM12 								GPIO_PIN_4
#define LM21 								GPIO_PIN_6
#define LM22 								GPIO_PIN_5
#define LM11_MASK 							3
#define LM12_MASK 							4
#define LM21_MASK 							6
#define LM22_MASK 							5
/* IR definitions */
#define SYSCTLPERIPH_IR1 					SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA)
#define SYSCTLPERIPH_IR2 					SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC)
#define IR1_PORT  							GPIO_PORTA_BASE
#define IR2_PORT  							GPIO_PORTC_BASE
#define IR1_PIN 							GPIO_PIN_2
#define IR2_PIN 							GPIO_PIN_4
#define IR1_PIN_MASK 						2
#define IR2_PIN_MASK 						4
#define WHITE1 								1<<IR1_PIN_MASK
#define WHITE2 								1<<IR2_PIN_MASK
#define BLACK 								0
/* Solenoid definitions */
#define SYSCTLPERIPH_SOLENOID 				SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD)
#define SOLENOID_PORT				 		GPIO_PORTD_BASE
#define SOLENOID_PIN1 						GPIO_PIN_2
#define SOLENOID_PIN_MASK1 					2
#define SOLENOID_PIN2                       GPIO_PIN_3
#define SOLENOID_PIN_MASK2                  3

/* Servo macros*/
#define SERVO1_PIN							M0PWM2
#define SERVO2_PIN							M1PWM1
/* Limit switch macros */
#define SYSCTLPERIPH_LIMIT1_SWITCH			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD)
#define LIMIT1_SWITCH_PORT					GPIO_PORTD_BASE
#define LIMIT1_SWITCH_PIN1					GPIO_PIN_2
#define LIMIT1_SWITCH_PIN2					GPIO_PIN_3
#define SYSCTLPERIPH_LIMIT2_SWITCH			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD)
#define LIMIT2_SWITCH_PORT					GPIO_PORTD_BASE
#define LIMIT2_SWITCH_PIN1					GPIO_PIN_6
#define LIMIT2_SWITCH_PIN2					GPIO_PIN_7

void setPWM(float pwm,int i);
unsigned absolute(float x);
void UART_TransmitString(char* string,int i);
void UART_OutDec(int x, int i);

//Parameter changer
extern float setShootPercent(float i);
extern int setPlaneAngle(int i);
extern long int getThrowerPosition(void);
extern void setThrowerPositionRelative(long int i);
extern void setThrowerPositionAbsolute(long int i);
#endif

