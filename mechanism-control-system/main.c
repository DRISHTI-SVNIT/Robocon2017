#define ANGLE_RESET 0

#include "userLib/common.h"
#include "userLib/init.h"
#include "userLib/pidController.h"
#include "userLib/movingArray.h"
#include <stdbool.h>
#include "angle.h"
#include "shoot.h"
#include "load.h"
#include "automation.h"
#include "LCD_16x2_595_lib.h"

int32_t maxPWM_throw = 10,maxPWM = 0;							//Random maxPWM value
int32_t maxPWM_angle = 10;							//Random maxPWM value
int32_t minPWM_throw = 0;						//Minimum PWM value for the throw motor to move
int32_t minPWM_angle = 0;						//Minimum PWM value for the angle motor to move
int memPlaneAngle = 0;

volatile float shootPercent = 1.0;
volatile int shoot = 0,load = 0,planeAngle = 0;			//UART packet value holders of the mechanism.
volatile int8_t enablePositionChange = 0;
bool loadEnable = false; 
bool autonomous_mode = false;
bool reset_mode = false;
bool timerEnable = false;
SET_VALUE GET_PARAM;
int POLE;
bool loaderChange = false;
bool loadComplete = true;
uint8_t currLoaderID = loader1;

//Interrupt routines prototype
void Timer0IntHandler(void);
void ISR_ANGLE(void);
void UARTIntHandler(void);

//Parameter changer
float setShootPercent(float i) {
    shootPercent = i;
    if(shootPercent > 1.0) {
        shootPercent = 1.0;
    }
    if(shootPercent < 0.1) {
        shootPercent = 0.1;
    }
    maxPWM_throw = maxPWM * shootPercent;
    return shootPercent;
}

int setPlaneAngle(int i) {
    planeAngle = i;
    if(planeAngle > MAX_ANGLE) {
        planeAngle = MAX_ANGLE;
    }
    if(planeAngle < -MAX_ANGLE) {
        planeAngle = -MAX_ANGLE;
    }
    cmd_angle(planeAngle);
    return planeAngle;
}

void setThrowerPositionRelative(long int i) {
    des_throw_counter = throw_counter + i;
    updateFirstStage();
}

void setThrowerPositionAbsolute(long int i) {
    des_throw_counter = i;
    updateFirstStage();
}

long int getThrowerPosition(void) {
    return QEIPositionGet(QEI0_BASE);
}

void reset(void) {
    loadEnable = false;
    Lcd_16x2_595_init();
    Lcd_clearScreen();
}

int main() {
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
	Lcd_16x2_595_init();
	initPIDController(throw_motor,0.001,0.0,0.0); //0.04
	initPIDController(angle_motor,9.0,0.0,0.0);
	IntMasterEnable();
	uart0Init();
	UARTFIFODisable(UART0_BASE);
	IntEnable(INT_UART0);
	UARTIntEnable(UART0_BASE, UART_INT_RX);
	Lcd_Print("System started");
	UART_TransmitString("System started.\r\n",0);
	maxPWM = SysCtlClockGet()/(PWMfrequency*8);
	maxPWM_throw = maxPWM;
	maxPWM_angle = maxPWM;
	minPWM_throw = maxPWM/20.0;             //16.0
	minPWM_angle = maxPWM/20.0;
	maxPWM_throw = maxPWM * shootPercent;	// 0.7 times for middle pole at 90 degree
	pwmInit();
	motorDirInit(angle_motor);
	motorDirInit(throw_motor);
	qeiInit();
	encoderInit(ISR_ANGLE,angle_motor);
	loadInit();
    uart5Init();
	timerInit();
	timerEnable = true;
	int semiCircle = convertThrowAngleToTicks(180);
	while(1) {
        Lcd_clearScreen();
        Lcd_Print("PA %d ",planeAngle);
        Lcd_Print("RPM %f ",shootPercent*100);
        Lcd_newLine();
        Lcd_Print("TA %f ",throw_angle);
        Lcd_Print("L%d ",currLoaderID);
        SysCtlDelay(5000000);
	    if(loadEnable == true){
            Lcd_clearScreen();
            Lcd_Print("RELOAD");
            memPlaneAngle = planeAngle;
            if(currLoaderID == loader1) {
                setPlaneAngle(5);
            } else if(currLoaderID == loader2) {
                setPlaneAngle(0);
            }
            reload(currLoaderID);
            loadEnable = false;
            loadComplete = true;
            while(moveThrower(des_throw_counter)!=1);
            planeAngle = setPlaneAngle(memPlaneAngle);
            SysCtlDelay(5000000);
	    }
	    else{
            if(shootComplete == 0){
                Lcd_clearScreen();
                Lcd_Print("SHOOT");
                SysCtlDelay(5000000);
            }
	    }
/*
        UARTCharPut(UART0_BASE,';');
        UART_OutDec(throw_counter,0);
        UARTCharPut(UART0_BASE,';');
        UART_OutDec(convertThrowAngleToTicks(LOAD_ANGLE1),0);
        UARTCharPut(UART0_BASE,';');
        UART_OutDec(loadPointHolder,0);
        UARTCharPut(UART0_BASE,';');
        UART_OutDec(throw_angle,0);
		UART_TransmitString("\r\n",0);
*/
	}
}

void Timer0IntHandler(void) {
   TimerIntClear(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
   if(timerEnable) {
       throw_counter = getThrowerPosition() ;
       throw_angle = convertTicksToThrowAngle(throw_counter);
        if(enablePositionChange == 0) {
            shootDisc(!shootComplete);
        } else {
            if(enablePositionChange == 1) {         //Clock
                setPWM(minPWM_throw,throw_motor);
            } else if(enablePositionChange == -1) { //Anticlock
                setPWM(-minPWM_throw,throw_motor);
            }
            updateDesiredStage();
            updateFirstStage();
        }
        changeAngle();
   }
}

void UARTIntHandler(void) {
	uint32_t ui32Status;
	ui32Status = UARTIntStatus(UART5_BASE, true); //get interrupt status
	UARTIntClear(UART5_BASE, ui32Status); //clear the asserted interrupts
	char data = UARTCharGet(UART5_BASE);//HWREG(UART5_BASE + UART_O_DR);
	/* Mode selection */
	if((data & 0b11111000) == 0b11111000){
	    reset_mode = true;
	    autonomous_mode = true;
	} else if((data & 0b11000000) == 0b11000000) {
	    autonomous_mode = false;
        reset_mode = true;
	} else {
	    autonomous_mode = false;
	    reset_mode = false;
	}
	/* Manual mode */
	if(autonomous_mode == false && reset_mode == false){
		uint8_t tempPlaneAngle = 0, tempRpm = 0, tempPosChange = 0;
		shoot = (data & 0b10000000);
		load = (data & 0b01000000);
		if(load != LOAD_DISC && loadEnable == false) {
			/*Plane angle routine*/
			tempPlaneAngle = (data & 0b00110000)>>4;
			switch(tempPlaneAngle) {
			case 1:
				planeAngle++;
				break;
			case 2:
				planeAngle--;
				break;
			}
			planeAngle = setPlaneAngle(planeAngle);
			/*RPM change routine*/
			tempRpm = (data & 0b00001100)>>2;
			switch(tempRpm) {
			case 1:
				shootPercent += 0.0125;
				break;
			case 2:
				shootPercent -= 0.0125;
				break;
			}
			shootPercent = setShootPercent(shootPercent);
	
			/*Throw position change routine*/
			tempPosChange = (data & 0b00000011);
			switch(tempPosChange) {
			case 0:
				enablePositionChange = 0;
				break;
			case 1:
				enablePositionChange = 1;
				break;
			case 2:
				enablePositionChange = -1;
				break;
			default:
				enablePositionChange = 0;
				break;
			}
	
			/*Shoot Disc*/
			if (shoot == SHOOT_DISC) {
				if (shootComplete == 1 && triggered == 0)
				{
					cmd_throw();
					triggered = 1;
					shootComplete = 0;
				}
			} else if (shoot == 0) {
				triggered=0;
			}

		} else {
			loadEnable = true;
	    }
	}
	else if (autonomous_mode  == true) {
	    POLE = (data & 0b00000111);
	    GET_PARAM = SET_PARAMETERS(POLE);
	    planeAngle = GET_PARAM.PLANE_ANGLE;
	    shootPercent = GET_PARAM.SHOOT_PERCENT;
	    throw_angle = GET_PARAM.THROW_ANGLE;
	    maxPWM_throw = maxPWM * shootPercent;
	} else if(reset_mode == true) {
            int resetData = data & 0b00111111;
            switch(resetData) {
            case 0b00010000:
                reset();
                Lcd_clearScreen();
                Lcd_Print("RESET");
                SysCtlDelay(2500000);
                Lcd_clearScreen();
                SysCtlDelay(2500000);
                Lcd_Print("RESET");
                SysCtlDelay(2500000);
                break;
            case 0b00000001:
                reload_manual(loader1,up);
                Lcd_clearScreen();
                Lcd_Print("LAODER 1 UP");
                SysCtlDelay(2500000);
                break;
            case 0b00000010:
                reload_manual(loader1,down);
                Lcd_clearScreen();
                Lcd_Print("LAODER 1 DOWN");
                SysCtlDelay(2500000);
                break;
            case 0b00000100:
                reload_manual(loader2,up);
                Lcd_clearScreen();
                Lcd_Print("LAODER 2 UP");
                SysCtlDelay(2500000);
                break;
            case 0b00001000:
                reload_manual(loader2,down);
                Lcd_clearScreen();
                Lcd_Print("LAODER 2 DOWN");
                SysCtlDelay(2500000);
                break;
            case 0b00100000:
                if(currLoaderID == loader1) {
                    currLoaderID = loader2;
                } else {
                    currLoaderID = loader1;
                }
                Lcd_clearScreen();
                Lcd_Print("LAODER CHANGED TO %d",currLoaderID);
                SysCtlDelay(2500000);
            }
	}
}

void ISR_ANGLE(void) {
	GPIOIntClear(ANGLE_ENCODER_PORT,ANGLE_ENCODER_CHANNELB);
	if(GPIOPinRead(ANGLE_ENCODER_PORT,ANGLE_ENCODER_CHANNELA)) {
		angle_counter++;
	} else {
		angle_counter--;
	}
}

void UART0Handler(void) {
	uint32_t ui32Status;
	ui32Status = UARTIntStatus(UART0_BASE, true); //get interrupt status
	UARTIntClear(UART0_BASE, ui32Status); //clear the asserted interrupts
	char char_data = UARTCharGet(UART0_BASE);
	if(char_data == 'u') {
		reload_manual(loader1,up);
	} else if(char_data == 'd') {
		reload_manual(loader1,down);
	} else if(char_data == 't') {
        reload_manual(loader2,up);
    } else if(char_data == 'b') {
        reload_manual(loader2,down);
    } else if(char_data == 'r') {
		loadEnable = true;
        UART_TransmitString("Loading :: \r\n",0);
	}  else if(char_data == 's') {
        UART_TransmitString("Servo angle 1 loader 1 :: \r\n",0);
	    moveServo(SERVO_ANGLE1,0);                                  //Servo hit
	} else if(char_data == 'a') {
        UART_TransmitString("Servo angle 2 loader 1:: \r\n",0);
        moveServo(SERVO_ANGLE2,0);                                  //Servo hit
    } else if(char_data == 'g') {
        UART_TransmitString("Servo angle 1 loader 2:: \r\n",0);
        moveServo(SERVO_ANGLE1,1);                                  //Servo hit
    } else if(char_data == 'f') {
        UART_TransmitString("Servo angle 2 loader 2:: \r\n",0);
        moveServo(SERVO_ANGLE2,1);                                  //Servo hit
    }
}
