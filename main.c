/*
 * AVR timer.c
 *
 * Created: 6/9/2026 10:57:41 AM
 * Author : ASUS
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void delay()
{
	TCCR0A&=~(1<<WGM00);
	TCCR0A&=~(1<<WGM01);
	TCCR0B&=~(1<<CS02);
	TCCR0B&=~(1<<CS01);
	TCCR0B |=(1<<CS00);
	for(uint16_t i=0;i<62500;i++){
	while(!(TIFR0 &(1<<TOV0)));
	TIFR0 |=(1<<TOV0);
	}
}



int main(void)
{
	DDRB|=(1<<DDB5);
	while (1)
	{
		PORTB|=(1<<PB5);
		delay();
		PORTB&=~(1<<PB5);
		delay();
	}
}

