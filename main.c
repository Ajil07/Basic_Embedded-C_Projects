/*
 * LCD Display.c
 *
 * Created: 6/10/2026 12:17:00 PM
 * Author : ASUS
 */ 
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "LCD.h"

int main(void)
{
   lcd_init();
    while (1) 
    {
		lcd_set_cursor(0,0);
		lcd_print("AJIL!");
		lcd_set_cursor(1,0);
		float a=07;
		lcd_print_float(a);
		_delay_ms(5000);
		lcd_clear();
		_delay_ms(1000);
    }
}

