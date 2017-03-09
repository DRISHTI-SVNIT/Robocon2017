//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//includes//
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "LCD_16x2_595_lib.h"

//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//Variables
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//------------------------------------------------------------------------------
//Global
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//Local
//------------------------------------------------------------------------------
static unsigned char UpperNibble, LowerNibble, bitsHigh, bitsLow,temp;
int l = 0;
//'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//Local Functions declaration
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
void PulseEnable ();
void shiftOut(unsigned char c);
void Lcd_595_Cmd(unsigned char c);
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//Function descriptions
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//Global Functions
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
void Lcd_16x2_595_init()
{

		SysCtlPeripheralEnable(lcd_SysCtlPeripheral);

		GPIOPinTypeGPIOOutput(lcd_port, Enable | DATA | CLOCK);

		GPIOPinWrite(lcd_port, (Enable | DATA | CLOCK), 0x00);

		SysCtlDelay(delay_12ms);
		shiftOut(0x03);
		PulseEnable ();
		SysCtlDelay(delay_2_5ms);

		shiftOut(0x03);
		PulseEnable ();
		SysCtlDelay(delay_2_5ms);

		shiftOut(0x03);
		PulseEnable ();
		SysCtlDelay(delay_2_5ms);

		shiftOut(0x02);
		PulseEnable ();
		SysCtlDelay(delay_2_5ms);

		Lcd_595_Cmd(0x28);  //Function set - number of display 2 lines

		Lcd_595_Cmd(0x08);  //Display off

		Lcd_595_Cmd(0x01);  //Display clear

		Lcd_595_Cmd(0x0F);  //Cursor - Display on/off control
}
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
// to send command
void Lcd_595_Cmd(unsigned char c)
{
    UpperNibble = c >> 4;
    LowerNibble = c & 0x0F;

    shiftOut(UpperNibble);
    PulseEnable ();

    shiftOut(LowerNibble);
    PulseEnable ();

    SysCtlDelay(delay_2_5ms);
}
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//to print character
void Lcd_595_send_character(unsigned char c)
{

    UpperNibble = c >> 4;
    bitsHigh = UpperNibble | 0x10;// 0x10 =>this is done to make RS pin high while sending data
    LowerNibble = c & 0x0F;
    bitsLow = LowerNibble | 0x10;
    l++;
    if(l>=32){
    	SysCtlDelay(20000000);
    	start_from_beginning();

	}
	if(l<16){
		shiftOut(bitsHigh);
    	PulseEnable ();
    	
      	shiftOut(bitsLow);
     	PulseEnable ();
	}
	else{
		if(l==16){
			Lcd_595_Cmd(0xC0);
		}
		shiftOut(bitsHigh);
    	PulseEnable ();
    	
      	shiftOut(bitsLow);
     	PulseEnable ();
	}
}
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
void Lcd_595_Chr(char row, char column, char out_char)
{
	Position_Lcd(row,column);
	Lcd_595_send_character(out_char);
}
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
void Lcd_595_text(char row, char column, char *text)
{
	Position_Lcd(row,column);
	sendAstring(text);
}
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//Local Functions
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
void start_from_beginning(){
	Lcd_595_Cmd(0x01);
	Position_Lcd(1,1);
}
void PulseEnable ()
{
	GPIOPinWrite(lcd_port, Enable, 0x01);//EN = 1;
	SysCtlDelay(delay_0_6us);
	GPIOPinWrite(lcd_port, Enable, 0x00);//EN = 0;
}
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
void shiftOut(unsigned char c)
{
   int i;
   for (i=7;i>=0;i--)
   {
	   GPIOPinWrite(lcd_port, CLOCK, 0x00);//CLOCK = 0
      if (c & (1<<i))
      {
       GPIOPinWrite(lcd_port, DATA, 0x02);//DATA = 1
      }
      else
      {
       GPIOPinWrite(lcd_port, DATA, 0x00);//DATA = 0
      }
       GPIOPinWrite(lcd_port, CLOCK, 0x20);//CLOCK = 1
   }

   SysCtlDelay(delay_12us);
   GPIOPinWrite(lcd_port, CLOCK, 0x00); //CLOCK = 0
   SysCtlDelay(delay_12us);
   GPIOPinWrite(lcd_port, CLOCK, 0x20); //CLOCK = 1
}
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
void Position_Lcd(unsigned char x, unsigned char y)
{
	 temp = 127 + y;
	 if (x == 2) temp = temp + 64;
	 Lcd_595_Cmd(temp);
	 l = y;
}
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//to print number
void send_number(unsigned long n) {
	unsigned long val = n;
	int arr[10];
	int len = 0;
	int j = 0,r = 0;
	if(val == 0){
	   Lcd_595_send_character(val + '0');
	}
	else{
        while(val!=0) {
             r = val%10;
            arr[len] = r;
            val = val/10;
            len++;
        }
        for( j=(len-1);j>=0;j--) {
            Lcd_595_send_character(arr[j]+'0');
        }
	}
}
//  END OF FILE
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//to print string
void sendAstring(char *ch)
{
    while(*ch!='\0'){
    	if(l>=32){
    		SysCtlDelay(20000000);
    		start_from_beginning();
		}
		Lcd_595_send_character(*ch);
		ch++;
	}
}

void sendFloat_number( double n){
    int32_t temp = n;
    float difference = n - (float)temp;
    int32_t num = difference*1000.0;

    if(l>=32){
    	SysCtlDelay(20000000);
    	start_from_beginning();

	}
	send_number(temp);
	Lcd_595_send_character('.');
	send_number(num);
}
void Lcd_Print( char* format,...){
	char *traverse;
	int i;
	char ch;
	char *s;
	double fl;

	va_list arg;
	va_start(arg,format);

	for(traverse = format; *traverse != '\0'; traverse++)
	    {
	        while( *traverse != '%'&& *traverse !='\0')
	        {
	            Lcd_595_send_character(*traverse);
	            traverse++;
	        }
			
	        if(*traverse!='\0'){
	        	traverse++;
			}
			else{
				break;
			}
			switch(*traverse){
			case 'd': i = va_arg(arg,int);
					  if(i<0)
					  {
						  i = -i;
						  Lcd_595_send_character('-');
					  }
					  send_number(i);
					  break;

			case 'c': ch = va_arg(arg,char);
					  Lcd_595_send_character(ch);
					  break;

			case 's': s = va_arg(arg,char*);
					  sendAstring(s);
					  break;

			case 'f': fl = va_arg(arg,double);
						if(fl<0.0)
					  {
						  fl = -fl;
						  Lcd_595_send_character('-');
					  }
					  sendFloat_number(fl);
					  break;
			}
	    }
	va_end(arg);

}

void Lcd_newLine(void) {
    Lcd_595_Cmd(0xC0);
    l = 17;
}

void Lcd_clearScreen(void) {
    Lcd_595_Cmd(0x01);
    l = 0;
}
