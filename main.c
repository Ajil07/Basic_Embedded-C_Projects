/*
 * Heat sensor.c
 *
 * Created: 6/10/2026 9:58:08 PM
 * Author : ASUS
 */ 

#define F_CPU 16000000UL 
#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"

int main(void)
{
   lcd_init();
   
   
   DDRC &= ~(1<<PC3);   // PC3 (ADC3) as input
   
   ADMUX|=(1<<REFS0);
   
   //ADMUX&=~(1<<REFS1);  //Set reference voltage to external 5v
   
   ADMUX|=(1<<MUX1);
   ADMUX|=(1<<MUX0);
   
   ADCSRA|=(1<<ADEN);
   
   //ADCSRA |=(1<<ADSC);
   
   ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
   //char tempStr[10];

    while (1) 
    {	ADCSRA |=(1<<ADSC);
		
		
	    while(ADCSRA & (1<<ADSC));
		
	    uint16_t adcread = ADC;
		float voltage = (adcread * 5.0) / 1024.0;
		float temperature = voltage *100.0;
	    
	    uint16_t temp_int = (uint16_t)temperature;
	    uint8_t temp_dec = (uint8_t)((temperature - temp_int) * 10);

		lcd_clear();
        lcd_set_cursor(0, 0);
        lcd_print("Temp:");

        lcd_set_cursor(0, 6);
        lcd_print_uint16(temp_int);
        lcd_print(".");
        lcd_print_uint16(temp_dec);
        lcd_print("C");

        lcd_set_cursor(1, 0);
        lcd_print("ADC:");
        lcd_print_uint16(adcread);

        _delay_ms(1000);
		DDRD |= (1<<DDD6);
		if ( temp_int>45)
		{ 
		DDRB|=(1<<DDB5);
	    PORTB|=(1<<PB5);
		
		
		DDRD |= (1<<DDD6); //////////////////////////////////////////////////////////////////////////
		
		//FAST PWM
		TCCR0A |= (1<<WGM00);
		TCCR0A |= (1<<WGM01);
		//NON INVERTING PWM
		TCCR0A &= ~(1<<COM0A0);
		TCCR0A |= (1<<COM0A1);
		//PRESCALAR TIMER CLK/1024
		TCCR0B &=~(1<<CS02);
		TCCR0B |=(1<<CS01);
		TCCR0B |=(1<<CS00);
		
		OCR0A = 154 ; //////////////////////////////////////////////////////////////////////////
		}
		if (temp_int<45)
		{
		PORTB&=~(1<<PB5);
		
		
		DDRD &=~ (1<<DDD6);
		}
		
		
		
    }
}

