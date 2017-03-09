#include "common.h"

void setPWM(float pwm,int i) {
	if(i == throw_motor) {
		if(pwm > maxPWM_throw) {
			pwm = maxPWM_throw;
		} else if(pwm < -maxPWM_throw) {
			pwm = -maxPWM_throw;
		}
		if(pwm > 0) {
			if(pwm < minPWM_throw) {
				pwm = minPWM_throw;
			}
	     	GPIOPinWrite(THROW_MOTOR_PORT,TM1|TM2,TM1_MASK);
			PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3, pwm);
		} else if(pwm < 0) {
			if(pwm > -minPWM_throw) {
				pwm = -minPWM_throw;
			}
	     	GPIOPinWrite(THROW_MOTOR_PORT,TM1|TM2,TM2_MASK);
			PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3, -pwm);
		} else {
			PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3, 1);
			GPIOPinWrite(THROW_MOTOR_PORT,TM1|TM2,0);
		}
	} else if(i == angle_motor) {
		if(pwm > maxPWM_angle) {
			pwm = maxPWM_angle;
		} else if(pwm < -maxPWM_angle) {
			pwm = -maxPWM_angle;
		}
		if(pwm > 0) {
			if(pwm < minPWM_angle) {
				pwm = minPWM_angle;
			}
			GPIOPinWrite(ANGLE_MOTOR_PORT,AM1|AM2,AM1_MASK);
			PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, pwm);
		} else if(pwm < 0) {
			if(pwm > -minPWM_angle) {
				pwm = -minPWM_angle;
			}
			GPIOPinWrite(ANGLE_MOTOR_PORT,AM1|AM2,AM2_MASK);
			PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, -pwm);
		} else {
			PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, 1);
			GPIOPinWrite(ANGLE_MOTOR_PORT,AM1|AM2,0);
		}
	}
}

unsigned int absolute(float x) {
	return ((x < 0) ? -x : x);
}

void UART_TransmitString(char *str,int i) {
	while(*str>0)	 {
		switch(i)	{
		case 0:
			UARTCharPut(UART0_BASE,(*str));
			break;
		case 1:
			UARTCharPut(UART1_BASE,(*str));
			break;
		case 2:
			UARTCharPut(UART2_BASE,(*str));
			break;
		case 3:
			UARTCharPut(UART3_BASE,(*str));
			break;
		case 4:
			UARTCharPut(UART4_BASE,(*str));
			break;
		case 5:
			UARTCharPut(UART5_BASE,(*str));
			break;
		case 6:
			UARTCharPut(UART6_BASE,(*str));
			break;
		case 7:
			UARTCharPut(UART7_BASE,(*str));
			break;
		}
		str++;
	}
}

void UART_OutUDec(unsigned long n,int i) {
	if(n >= 10){
		UART_OutUDec(n/10,i);
		n = n%10;
	}
	switch(i)
	{
	case 0:
		UARTCharPut(UART0_BASE,(n+'0'));
		break;
	case 1:
		UARTCharPut(UART1_BASE,(n+'0'));
		break;
	case 2:
		UARTCharPut(UART2_BASE,(n+'0'));
		break;
	case 3:
		UARTCharPut(UART3_BASE,(n+'0'));
		break;
	case 4:
		UARTCharPut(UART4_BASE,(n+'0'));
		break;
	case 5:
		UARTCharPut(UART5_BASE,(n+'0'));
		break;
	case 6:
		UARTCharPut(UART6_BASE,(n+'0'));
		break;
	case 7:
		UARTCharPut(UART7_BASE,(n+'0'));
	    break;
	}
}

void UART_OutDec(int x, int i) {
	if(x < 0) {
		switch(i)
		{
		case 0:
			UARTCharPut(UART0_BASE,'-');
			break;
		case 1:
			UARTCharPut(UART1_BASE,'-');
			break;
		case 2:
			UARTCharPut(UART2_BASE,'-');
			break;
		case 3:
			UARTCharPut(UART3_BASE,'-');
			break;
		case 4:
			UARTCharPut(UART4_BASE,'-');
			break;
		case 5:
			UARTCharPut(UART5_BASE,'-');
			break;
		case 6:
			UARTCharPut(UART6_BASE,'-');
			break;
		case 7:
			UARTCharPut(UART7_BASE,'-');
			break;
		}
		x *= -1;
	}
	UART_OutUDec(x, i);
}

