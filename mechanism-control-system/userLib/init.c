#include "init.h"
#include "../shoot.h"

void motorDirInit(int i) {
	if(i == throw_motor) {
		SYSCTLPERIPH_THROW_MOTOR;
		GPIOPinTypeGPIOOutput(THROW_MOTOR_PORT, TM1|TM2);
	} else if(i == angle_motor) {
		SYSCTLPERIPH_ANGLE_MOTOR;
		GPIOPinTypeGPIOOutput(ANGLE_MOTOR_PORT, AM1|AM2);
	}
}

void encoderInit(void (*pfHandler)(void),int i) {
	if(i == throw_motor) {
		/*QEI init*/
	} else if(i == angle_motor) {
		SYSCTLPERIPH_ANGLE_ENC;
		GPIOPinTypeGPIOInput(ANGLE_ENCODER_PORT, ANGLE_ENCODER_CHANNELB);
		GPIOPadConfigSet(ANGLE_ENCODER_PORT, ANGLE_ENCODER_CHANNELB,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
		GPIOIntDisable(ANGLE_ENCODER_PORT, ANGLE_ENCODER_CHANNELB);
		GPIOIntClear(ANGLE_ENCODER_PORT, ANGLE_ENCODER_CHANNELB);
		GPIOIntRegister(ANGLE_ENCODER_PORT, pfHandler);
		GPIOIntTypeSet(ANGLE_ENCODER_PORT, ANGLE_ENCODER_CHANNELB,GPIO_RISING_EDGE);
		GPIOIntEnable(ANGLE_ENCODER_PORT, ANGLE_ENCODER_CHANNELB);
		GPIOPinTypeGPIOInput(ANGLE_ENCODER_PORT, ANGLE_ENCODER_CHANNELA);
		GPIOPadConfigSet(ANGLE_ENCODER_PORT, ANGLE_ENCODER_CHANNELA,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	}
}

void qeiInit(void) {
	SYSCTLPERIPH_THROW_ENC;
	SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI0);
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;
	GPIOPinConfigure(THROW_ENCODER_CHANNELA_PINCONFIG);
	GPIOPinConfigure(THROW_ENCODER_CHANNELB_PINCONFIG);
	GPIOPinTypeQEI(THROW_ENCODER_PORT, THROW_ENCODER_CHANNELA |  THROW_ENCODER_CHANNELB);
	QEIDisable(QEI0_BASE);
	QEIIntDisable(QEI0_BASE,QEI_INTERROR | QEI_INTDIR | QEI_INTTIMER | QEI_INTINDEX);
	QEIConfigure(QEI0_BASE, (QEI_CONFIG_CAPTURE_A_B  | QEI_CONFIG_NO_RESET 	| QEI_CONFIG_QUADRATURE | QEI_CONFIG_SWAP), 0xFFFFFFFF);
	QEIEnable(QEI0_BASE);
	QEIPositionSet(QEI0_BASE, STEP);
}

void timerInit(void) {
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	TimerConfigure(TIMER0_BASE,TIMER_CFG_A_PERIODIC);
	TimerLoadSet(TIMER0_BASE,TIMER_A,(uint32_t)(SysCtlClockGet()/(PIDfrequency)));
	IntEnable(INT_TIMER0A);
	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	TimerEnable(TIMER0_BASE, TIMER_A);
}

void uart0Init(void) {
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	GPIOPinConfigure(GPIO_PA0_U0RX);
	GPIOPinConfigure(GPIO_PA1_U0TX);
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 38400,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}

void uart1Init(void) {
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	GPIOPinConfigure(GPIO_PB0_U1RX);
	GPIOPinConfigure(GPIO_PB1_U1TX);
	GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 38400,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
	UARTFIFODisable(UART1_BASE);
    IntEnable(INT_UART1);
    UARTIntEnable(UART1_BASE, UART_INT_RX);
}

void uart5Init(void) {
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART5);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	GPIOPinConfigure(GPIO_PE4_U5RX);
	GPIOPinTypeUART(GPIO_PORTE_BASE, GPIO_PIN_4);
	UARTConfigSetExpClk(UART5_BASE, SysCtlClockGet(),9600,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
	UARTFIFODisable(UART5_BASE);
	IntEnable(INT_UART5);
	UARTIntEnable(UART5_BASE, UART_INT_RX);
}

void pwmInit(void) {
	SysCtlPWMClockSet(SYSCTL_PWMDIV_8);
	//Angle motor PD0
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_0);
	GPIOPinConfigure(GPIO_PD0_M1PWM0);
	PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);
	PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, SysCtlClockGet()/(8*PWMfrequency));
	PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT, true);
	PWMGenEnable(PWM1_BASE, PWM_GEN_0);

	//Throw motor PE5
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);//enable GPIOD port
	GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_5);//giving output of pwm at PD0
	GPIOPinConfigure(GPIO_PE5_M1PWM3);//configuring generator 0 of module 1 of pwm
	PWMGenConfigure(PWM1_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN);//configure a pwm generator
	PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, SysCtlClockGet()/(8*PWMfrequency));//sets the period of pwm generator
	PWMOutputState(PWM1_BASE, PWM_OUT_3_BIT, true);//enables pwm output
	PWMGenEnable(PWM1_BASE, PWM_GEN_1);//enables the timer counter of pwm generator block

    //Servo Loader 1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_4);
    GPIOPinConfigure(GPIO_PB4_M0PWM2);
    PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN);
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, SysCtlClockGet()/(8*50));
    PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, true);
    PWMGenEnable(PWM0_BASE, PWM_GEN_1);

    //Servo loader 2
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_1);
    GPIOPinConfigure(GPIO_PD1_M0PWM7);
    PWMGenConfigure(PWM0_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN);
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, SysCtlClockGet()/(8*50));
    PWMOutputState(PWM0_BASE, PWM_OUT_7_BIT, true);
    PWMGenEnable(PWM0_BASE, PWM_GEN_3);
}

void setServoAngle(int i,float time) {
    float ticks_for_duty_cycle = time/(8/(float)SysCtlClockGet()) - 1;
    if(i == loader1) {
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2,ticks_for_duty_cycle);
    } else if (i == loader2) {
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7,ticks_for_duty_cycle);
    }
}
