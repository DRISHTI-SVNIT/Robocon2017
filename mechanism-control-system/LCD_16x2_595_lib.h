#ifndef _LCD_16X2_595_LIB_H
#define _LCD_16X2_595_LIB_H

//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//includes
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//Constants (Local and Global)
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//!!!You can rewrite these definitions as you need
//by default LCD is connected to PORTB
#define lcd_SysCtlPeripheral   SYSCTL_PERIPH_GPIOB
#define lcd_port               GPIO_PORTB_BASE
#define Enable                 GPIO_PIN_0
#define DATA                   GPIO_PIN_1
#define CLOCK                  GPIO_PIN_5


//by default these definitions are  is for 50 MHz processor speed
//you must recalculate definitions if you are using another as shown
#define delay_12ms     200000       // =(SysCtlClockGet()/3000)*12  //for example (50000000/3000)*12=200000
#define delay_2_5ms    41666        // =(SysCtlClockGet()/3000)*2.5
#define delay_12us     200          // =(SysCtlClockGet()/3000000)*12
#define delay_0_6us    10           // =(SysCtlClockGet()/3000000)*0.6

//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
#define LCD_CLEAR            0x01   // Clear display
#define LCD_CURSOR_ON        0x0E   // Cursor on
#define LCD_CURSOR_OFF       0x0C   // Turn off cursor
#define LCD_BLINK_CURSOR_ON  0x0F   // Blink cursor on//Turns on the LCD display and Sets a BLINKING CURSOR
#define LCD_BLINK_CURSOR_OFF 0x0E   // Cursor No Blink
#define LCD_UNDERLINE_ON     0xF1   // Underline cursor on
#define LCD_UNDERLINE_OFF    0x0D

#define LCD_TURN_ON          0x0C   // Turn Lcd display on
#define LCD_TURN_OFF         0x08   // Turn Lcd display off
#define INCREMENT            0x07   // Entry mode increment
#define DECREMENT            0x05   // Entry mode decrement
#define SHIFT_ON             0x07   // Display shift on
#define SHIFT_OFF            0x06   // Display shift off
#define SHIFT_LEFT           0x1C   // Text shift Left
#define SHIFT_RIGHT          0x18   // Display shift Right

#define FOUR_BIT             0x2F  // 4-bit Interface
#define EIGHT_BIT            0x3F  // 8-bit Interface
#define LINE_5X7             0x33  // 5x7 characters, single line
#define LINE_5X10            0x37  // 5x10 characters
#define LINES_5X7            0x3B  // 5x7 characters, multiple line


//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//Type definitions
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//Define global variables
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//declaration global functions
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
extern void Lcd_16x2_595_init();
extern void Lcd_595_Cmd(unsigned char c);
extern void Lcd_595_send_character(unsigned char c);
extern void Lcd_595_Chr(char row, char column, char out_char);
extern void Lcd_595_text(char row, char column, char *text);
void send_number(unsigned long n);
void sendAstring(char *ch);
void sendFloat_number( double n);
void Position_Lcd(unsigned char x, unsigned char y);
void Lcd_Print( char* format,...);
void start_from_beginning();
void Lcd_newLine();
void Lcd_clearScreen();
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//Section of the macros
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
#endif
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//  END OF FILE
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
