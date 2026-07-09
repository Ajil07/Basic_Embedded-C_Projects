/*
 * receiver.c
 *
 * Created: 6/11/2026 9:34:37 PM
 * Author : ASUS
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	UBRR0H = 0;
	UBRR0L = 103;

	// Enable Receiver and Transmitter
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	// USART configuration:
	// Asynchronous, No parity, 1 stop bit, 8 data bits
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	
	char str[6];
	uint8_t i = 0;

	while (1)
	{
		// Wait for a character to be received
		while (!(UCSR0A & (1 << RXC0)));

		// Read received character
		char data = UDR0;

		// Store first 5 characters
		if (i < 5)
		{
			str[i] = data;
			i++;

			if (i == 5)
			{
				str[5] = '\0';   // Complete string
				i = 0;          
			}
		}

		// Echo the received character back
		while (!(UCSR0A & (1 << UDRE0)));
		UDR0 = data;
	}
}
