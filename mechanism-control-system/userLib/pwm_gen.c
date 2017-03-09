#include "pwm_gen.h"

volatile float ticks_for_pwm_frequency;
volatile float ticks_for_duty_cycle;
volatile uint8_t prescalar;

void enable_pwm_clock(uint8_t pwm_clk_prescalar)
{
	switch(pwm_clk_prescalar)
	{
		case 1:
		{
		prescalar = 1;
		SysCtlPWMClockSet(PWM_PRESCALE_1);
		}
		break;
		
		case 2:
		{
		}
		prescalar = 2;
		SysCtlPWMClockSet(PWM_PRESCALE_2);
	 break;
		
		case 4:
		{
		prescalar = 4;
		SysCtlPWMClockSet(PWM_PRESCALE_4);
		}
		break;
		
		case 8:
		{
		prescalar = 8;
		SysCtlPWMClockSet(PWM_PRESCALE_8);
		}	
		break;
		
		case 16:
		{
		prescalar = 16;
		SysCtlPWMClockSet(PWM_PRESCALE_16);
		}
		break;	
		
		case 32:
		{
		prescalar = 32;
		SysCtlPWMClockSet(PWM_PRESCALE_32);	
		}
		break;
		
		case 64:
		{
		prescalar = 64;
		SysCtlPWMClockSet(PWM_PRESCALE_64);
		}
		break;
		
	}
}

void config_pwm(uint8_t MPWM,uint8_t count_dir,uint8_t pwm_frequency)
{
	ticks_for_pwm_frequency = (((float)SysCtlClockGet() / prescalar)/pwm_frequency) - 1;
	switch(MPWM)
	{
			case 10 :
			{
			SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
			GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_6);
			GPIOPinConfigure(GPIO_PB6_M0PWM0);
			if(count_dir == COUNT_UP_DOWN)
			{
				PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_UP_DOWN);
			}
			else if(count_dir == COUNT_DOWN)
			{
				PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);
			}
			PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, ticks_for_pwm_frequency);
			}
			break;
			
			
			case 11 :
			{
			SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
			GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_7);
			GPIOPinConfigure(GPIO_PB7_M0PWM1);
			if(count_dir == COUNT_UP_DOWN)
			{
				PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_UP_DOWN);
			}
			else if(count_dir == COUNT_DOWN)
			{
				PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);
			}
			PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, ticks_for_pwm_frequency);
			}
			break;
			
			
			case 12 :
			{
			SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
			GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_4);
			GPIOPinConfigure(GPIO_PB4_M0PWM2);
			if(count_dir == COUNT_UP_DOWN)
			{
				PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_UP_DOWN);
			}
			else if(count_dir == COUNT_DOWN)
			{
				PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN);
			}
			PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, ticks_for_pwm_frequency);
			}
			break;
			
			
			case 13 :
			{
/*			SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
			GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_5);
			GPIOPinConfigure(GPIO_PB5_M0PWM3);
			if(count_dir == COUNT_UP_DOWN)
			{
				PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_UP_DOWN);
			}
			else if(count_dir == COUNT_DOWN)
			{
				PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN);
			}*/
			PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, ticks_for_pwm_frequency);
			}
			break;

			case 14 :
			{
			SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
			GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_4);
			GPIOPinConfigure(GPIO_PE4_M0PWM4);
			if(count_dir == COUNT_UP_DOWN)
			{
				PWMGenConfigure(PWM0_BASE, PWM_GEN_2, PWM_GEN_MODE_UP_DOWN);
			}
			else if(count_dir == COUNT_DOWN)
			{
				PWMGenConfigure(PWM0_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN);
			}
			PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, ticks_for_pwm_frequency);
			}
			break;
			
			case 15 :
			{
			SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
			GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_5);
			GPIOPinConfigure(GPIO_PE5_M0PWM5);
			if(count_dir == COUNT_UP_DOWN)
			{
				PWMGenConfigure(PWM0_BASE, PWM_GEN_2, PWM_GEN_MODE_UP_DOWN);
			}
			else if(count_dir == COUNT_DOWN)
			{
				PWMGenConfigure(PWM0_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN);
			}
			PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, ticks_for_pwm_frequency);
			}
			break;
			
			
			case 16 :
			{
			SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
			GPIOPinTypePWM(GPIO_PORTC_BASE, GPIO_PIN_4);
			GPIOPinConfigure(GPIO_PC4_M0PWM6);
			if(count_dir == COUNT_UP_DOWN)
			{
				PWMGenConfigure(PWM0_BASE, PWM_GEN_3, PWM_GEN_MODE_UP_DOWN);
			}
			else if(count_dir == COUNT_DOWN)
			{
				PWMGenConfigure(PWM0_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN);
			}
			PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, ticks_for_pwm_frequency);
			}
			break;
			
			
			case 17 :
			{
			SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
			GPIOPinTypePWM(GPIO_PORTC_BASE, GPIO_PIN_5);
			GPIOPinConfigure(GPIO_PC5_M0PWM7);
			if(count_dir == COUNT_UP_DOWN)
			{
				PWMGenConfigure(PWM0_BASE, PWM_GEN_3, PWM_GEN_MODE_UP_DOWN);
			}
			else if(count_dir == COUNT_DOWN)
			{
				PWMGenConfigure(PWM0_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN);
			}
			PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, ticks_for_pwm_frequency);
			}
			break;

			case 20 :
			{
			SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
			GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_0);
			GPIOPinConfigure(GPIO_PD0_M1PWM0);	
			if(count_dir == COUNT_UP_DOWN)
			{
				PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_UP_DOWN);
			}
			else if(count_dir == COUNT_DOWN)
			{
				PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);
			}
			PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, ticks_for_pwm_frequency);
			}
			break;
			
			case 21 :
			{
			SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
			GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_1);
			GPIOPinConfigure(GPIO_PD1_M1PWM1);
			if(count_dir == COUNT_UP_DOWN)
			{
				PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_UP_DOWN);
			}
			else if(count_dir == COUNT_DOWN)
			{
				PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);
			}
				PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, ticks_for_pwm_frequency);
			}
			break;
			case 22 :
			{
			SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
			GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_4);
			GPIOPinConfigure(GPIO_PE4_M1PWM2);	
			if(count_dir == COUNT_UP_DOWN)
			{
				PWMGenConfigure(PWM1_BASE, PWM_GEN_1, PWM_GEN_MODE_UP_DOWN);
			}
			else if(count_dir == COUNT_DOWN)
			{
				PWMGenConfigure(PWM1_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN);
			}
				PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, ticks_for_pwm_frequency);
			}
			break;
			
			case 23 :
			{
			SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
			GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_5);
			GPIOPinConfigure(GPIO_PE5_M1PWM3);	
			if(count_dir == COUNT_UP_DOWN)
			{
				PWMGenConfigure(PWM1_BASE, PWM_GEN_1, PWM_GEN_MODE_UP_DOWN);
			}
			else if(count_dir == COUNT_DOWN)
			{
				PWMGenConfigure(PWM1_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN);
			}
				PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, ticks_for_pwm_frequency);
			}
			break;
			
			case 24 :
			{
			SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
			GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_0);
			GPIOPinConfigure(GPIO_PF0_M1PWM4);	
			if(count_dir == COUNT_UP_DOWN)
			{
				PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_UP_DOWN);
			}
			else if(count_dir == COUNT_DOWN)
			{
				PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN);
			}
				PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, ticks_for_pwm_frequency);
			}
			break;
				
			case 25 :
			{
			SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
			GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1);
			GPIOPinConfigure(GPIO_PF1_M1PWM5);	
			if(count_dir == COUNT_UP_DOWN)
			{
				PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_UP_DOWN);
			}
			else if(count_dir == COUNT_DOWN)
			{
				PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN);
			}
				PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, ticks_for_pwm_frequency);
			}
			break;
			
			case 26 :
			{
			SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
			GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_2);
			GPIOPinConfigure(GPIO_PF2_M1PWM6);	
			if(count_dir == COUNT_UP_DOWN)
			{
				PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_UP_DOWN);
			}
			else if(count_dir == COUNT_DOWN)
			{
				PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN);
			}
				PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, ticks_for_pwm_frequency);
			}
			break;
			
			case 27 :
			{
			SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
			GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_3);
			GPIOPinConfigure(GPIO_PF3_M1PWM7);	
			if(count_dir == COUNT_UP_DOWN)
			{
				PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_UP_DOWN);
			}
			else if(count_dir == COUNT_DOWN)
			{
				PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN);
			}
				PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, ticks_for_pwm_frequency);
			}
			break;
	}

}

void set_pwm(uint8_t MPWM,uint8_t select,uint8_t duty_cycle,float time_period_in_sec) 
{
	if(select == 0)
	{
	ticks_for_duty_cycle = ((ticks_for_pwm_frequency+1)/100*duty_cycle)-1 ;	
	}
	else if (select == 1)
	{
	ticks_for_duty_cycle = time_period_in_sec/(prescalar/(float)SysCtlClockGet()) - 1;
	}
	switch(MPWM)
	{
		case 10 :
			{
			PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0,ticks_for_duty_cycle);
			PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, true);
			PWMGenEnable(PWM0_BASE,PWM_GEN_0);	
			}
			break;
	
		case 11	:
			{
			PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1,ticks_for_duty_cycle);
			PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, true);
			PWMGenEnable(PWM0_BASE,PWM_GEN_0);
			}
			break;
			
		case 12 :
			{
			PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2,ticks_for_duty_cycle);
			PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, true);
			PWMGenEnable(PWM0_BASE, PWM_GEN_1);
			}
			break;
			
		case 13 :
			{
			PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3,ticks_for_duty_cycle);
			PWMOutputState(PWM0_BASE, PWM_OUT_3_BIT, true);
			PWMGenEnable(PWM0_BASE, PWM_GEN_1);
			}
			break;
		
		case 14 :
			{
			PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4,ticks_for_duty_cycle);
			PWMOutputState(PWM0_BASE, PWM_OUT_4_BIT, true);
			PWMGenEnable(PWM0_BASE, PWM_GEN_2);
			}
			
		case 15 :
			{
			PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5,ticks_for_duty_cycle);
			PWMOutputState(PWM0_BASE, PWM_OUT_5_BIT, true);
			PWMGenEnable(PWM0_BASE, PWM_GEN_2);
			}
			
		case 16 :
			{
			PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6,ticks_for_duty_cycle);
			PWMOutputState(PWM0_BASE, PWM_OUT_6_BIT, true);
			PWMGenEnable(PWM0_BASE, PWM_GEN_3);
			}
			
		case 17 :
			{
			PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7,ticks_for_duty_cycle);
			PWMOutputState(PWM0_BASE, PWM_OUT_7_BIT, true);
			PWMGenEnable(PWM0_BASE, PWM_GEN_3);
			}
		case 20 :
			{
			PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0,ticks_for_duty_cycle);
			PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT, true);
			PWMGenEnable(PWM1_BASE, PWM_GEN_0);		
			}
			break;
	
		case 21	:
			{
			PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1,ticks_for_duty_cycle);
			PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, true);
			PWMGenEnable(PWM0_BASE, PWM_GEN_3);
			}
			break;
			
		case 22 :
			{
			PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2,ticks_for_duty_cycle);
			PWMOutputState(PWM1_BASE, PWM_OUT_2_BIT, true);
			PWMGenEnable(PWM1_BASE, PWM_GEN_1);
			}
			break;
			
		case 23 :
			{
			PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3,ticks_for_duty_cycle);
			PWMOutputState(PWM1_BASE, PWM_OUT_3_BIT, true);
			PWMGenEnable(PWM1_BASE, PWM_GEN_1);
			}
			break;
		
		case 24 :
			{
			PWMPulseWidthSet(PWM1_BASE, PWM_OUT_4,ticks_for_duty_cycle);
			PWMOutputState(PWM1_BASE, PWM_OUT_4_BIT, true);
			PWMGenEnable(PWM1_BASE, PWM_GEN_2);
			}
			
		case 25 :
			{
			PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5,ticks_for_duty_cycle);
			PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true);
			PWMGenEnable(PWM1_BASE, PWM_GEN_2);
			}
			
		case 26 :
			{
			PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6,ticks_for_duty_cycle);
			PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, true);
			PWMGenEnable(PWM1_BASE, PWM_GEN_3);
			}
			
		case 27 :
			{
			PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7,ticks_for_duty_cycle);
			PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT, true);
			PWMGenEnable(PWM1_BASE, PWM_GEN_3);
			}
	}
	
}

