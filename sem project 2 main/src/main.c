#define F_CPU 16000000UL //needs to be defined for the delay functions to work.
#define BAUD 9600
#define NUMBER_STRING 1001

#include <avr/io.h> //used for pins input/output
#include <util/delay.h> //here the delay functions are found
#include <stdio.h> //used for printf function.
#include "usart.h"//for uart output to pc. Debugging purposes

#include "i2cmaster.h"
#include "lcd.h"
#include "lm75.h"

//Declare global variables etc. here

//Declare function prototypes here

int main(void)
{   	 
	uart_init();//initialize communication with PC - debugging
	io_redirect();//redirect printf function to uart, so text will be shown on PC or Nextion Screen

// initialize i2c communication 
	i2c_init();
// initialize LCD display
	LCD_init();
// initialize temperature sensor
	lm75_init();

// Configuration of LCD display  
	DDRD = 0xFF; // I/O board:PD4_7 as outputs, for LEDs
	PORTD = 0x00; // Set output LEDs to off
// Configuration of buttons
	DDRC = 0xF0; //I/O board PC0...3 as inputs, for buttons
	PORTC = 0x3F; // Enable install pull at PC0..3 inputs

//Put code in here

}

//Put in function implementations here

