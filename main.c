/*
 * ADC.c
 *
 * Created: 6/10/2026 3:05:55 PM
 * Author : ASUS
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"

int main(void)
{ 
	DDRD |=(1<<PC3);
	
	ADMUX|=(1<<REFS0);
	ADMUX&=~(1<<REFS1);  //Set reference voltage to external 5v
	
	ADMUX&=~(1<<MUX3);
	ADMUX&~(1<<MUX2);
	ADMUX|=(1<<MUX1);  
	ADMUX|=(1<<MUX0); 
	
	ADCSRA|=(1<<ADEN);
	
	ADCSRA |=(1<<ADSC);
	
    while (1) 
	{ 
		ADCSRA |=(1<<ADSC);
		while(ADCSRA & (1<<ADSC));
		uint16_t adcread = ADC;
		
		
		lcd_set_cursor(0,0);
		lcd_print("ADC VALUE");
		lcd_set_cursor(1,0);
		lcd_print_uint16(adcread);
		_delay_ms(1000);
		
    }
}

