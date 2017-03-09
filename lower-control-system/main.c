#define HW_TEST 0

#if HW_TEST == 1
#include "HWtest.h"
#endif

#include "userLib/common.h"
#include "userLib/init.h"
#include "userLib/pidController.h"
#include "userLib/movingArray.h"

#define KP_motorA 1.0
#define KI_motorA 0.0
#define KD_motorA 6.0
#define KP_motorB 1.0
#define KI_motorB 0.0
#define KD_motorB 6.0

volatile float desiredRPM[2] = {0.0,0.0}, currentRPM[2] = {0.0,0.0}, out[2] = {0.0,0.0},bufferDesiredRPM[2] = {0.0,0.0};
int uartReceiveCount = 0;
int32_t maxPWM = 10;
int32_t minPWM = 0;

int main() {
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
	uart0Init();
    maxPWM = SysCtlClockGet()/(PWMfrequency*2);
#if HW_TEST == 0
	initPIDController(A,KP_motorA,KI_motorA,KD_motorA);
	initPIDController(B,KP_motorB,KI_motorB,KD_motorB);
	motorDirInit();
	uart5Init();
	pwmInit();
	maxPWM = SysCtlClockGet()/(PWMfrequency*2);
	qeiInit();
	setPWM(0,A);
	setPWM(0,B);
	IntMasterEnable();
	while(1) {
		GraphPlot0(currentRPM[A],desiredRPM[A],currentRPM[B],desiredRPM[B]);
	}
#elif HW_TEST == 1
	/*Type hardware test codes here*/
	//testMotor(A,maxPWM/2);
	//testMotor(B,maxPWM/2);
	testBothEncoder(maxPWM/4,maxPWM/4);//-maxPWM/2.0);
	while(1) {
	    GraphPlot0(currentRPM[A],desiredRPM[A],currentRPM[B],desiredRPM[B]);
//		UART_OutDec(currentRPM[A],0);
//		UARTCharPut(UART0_BASE,',');
//		UART_OutDec(currentRPM[B],0);
//		UARTCharPut(UART0_BASE,0x0D);

	}
#endif

}

void Timer0IntHandler(void) {
	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	// Clear the timer interrupt
}

void UARTIntHandler(void) {
	uint32_t ui32Status;
	ui32Status = UARTIntStatus(UART5_BASE, true); //get interrupt status
	UARTIntClear(UART5_BASE, ui32Status); //clear the asserted interrupts
	char data = HWREG(UART5_BASE + UART_O_DR);
	if(data == 0x0A) {
		uartReceiveCount = 0;
	} else {
		switch(uartReceiveCount) {
			case 0:
				bufferDesiredRPM[A] = ((data * ((data & 0x01) ? -1 : 1)));
				break;
			case 1:
				bufferDesiredRPM[B] = ((data * ((data & 0x01) ? -1 : 1)));
				desiredRPM[A] = bufferDesiredRPM[A] * GEAR_RATIO;
				desiredRPM[B] = bufferDesiredRPM[B] * GEAR_RATIO;
				break;
		}
		uartReceiveCount++;
	}
}

void QEI0IntHandler(void) {
	QEIIntClear(QEI0_BASE, QEI_INTTIMER);
	currentRPM[A] = movingArrayOut(A,calculateRPM(A));
#if HW_TEST == 0
	if(desiredRPM[A]!=0) {
		out[A] += PID(A,desiredRPM[A] - currentRPM[A]);
	} else {
		out[A] = 0;
	}
	setPWM(out[A],A);
#endif
}

void QEI1IntHandler(void) {
	QEIIntClear(QEI1_BASE, QEI_INTTIMER);
	currentRPM[B] = movingArrayOut(B,calculateRPM(B));
#if HW_TEST == 0
	if(desiredRPM[B]!=0) {
		out[B] += PID(B,desiredRPM[B] - currentRPM[B]);
	} else {
		out[B] = 0;
	}
	setPWM(out[B],B);
#endif
}
