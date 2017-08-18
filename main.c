#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>


#define F_CPU 8000000UL
#include <util/delay.h>

#define IRQS_PER_SECOND    1000						// Fuer optimale Genauigkeit muss
													// IRQS_PER_SECOND ein Teiler von F_CPU sein
													// und IRQS_PER_SECOND ein Vielfaches von 100.
													// Ausserdem muss gelten F_CPU / IRQS_PER_SECOND <= 65536
													// 500 µs //

#define IRQS_PER_10MS     (IRQS_PER_SECOND / 1000)	// Anzahl IRQs pro 10 Millisekunden

// Gültigkeitsprüfung.
// Bei ungeeigneten Werten gibt es einen Compilerfehler
#if (F_CPU/IRQS_PER_SECOND > 65536) || (IRQS_PER_10MS < 1) || (IRQS_PER_10MS > 255)
#   error Diese Werte fuer F_CPU und IRQS_PER_SECOND
#   error sind ausserhalb des gueltigen Bereichs!
#endif

uint8_t ms, ms10, ms100, sec;
uint8_t up = 0;
uint8_t down;
uint8_t on;
uint8_t up_ms;
uint16_t result = 0;
uint16_t adc(void);


ISR(TIMER1_COMPA_vect)
{
  static uint8_t interrupt_num_10ms;				// zaehlvariable deklarieren
      
    if (++interrupt_num_10ms == IRQS_PER_10MS)    	// interrupt_num_10ms erhöhen und mit Maximalwert vergleichen
    {
        interrupt_num_10ms = 0;						// interrupt_num_10ms zurücksetzen
		ms++;										// jede Millisekunde
    }
	
	if(ms == 10)									// Geht alle 10 Millisekunden rein
	{
		ms = 0;
		ms10++;
		up_ms++;
	}
	
	if(ms10 == 10)
	{
		ms10 = 0;
		ms100++;
		
	}
	
	if(ms100 == 10)
	{
		ms100 = 0;
		
		sec++;
		up++;
		down++;
	}
	
	if(up == 5)
	{
		on = 1;	
	}
	
	

	
	
}//End of ISR


void led( short y, short x, short z)
{
	DDRA = 0x00;
	DDRB = 0x00;
	DDRC = 0x00;
	DDRD = 0x00;

	switch(y)
	{
		case 1: switch(x)
				{
					case 1: switch(z)
							{
								case 1: DDRA |= (1<<PD0);
										DDRD |= (1<<PD3);	
			
										PORTA |= (1<<PD0);
										PORTD &= ~(1<<PD3);
										break;
								case 2: DDRA |= (1<<PD1);
										DDRD |= (1<<PD3);	
			
										PORTA |= (1<<PD1);
										PORTD &= ~(1<<PD3);
										break;
								case 3: DDRA |= (1<<PD2);
										DDRD |= (1<<PD3);	
			
										PORTA |= (1<<PD2);
										PORTD &= ~(1<<PD3);
										break;
								case 4: DDRA |= (1<<PD3);
										DDRD |= (1<<PD3);	
			
										PORTA |= (1<<PD3);
										PORTD &= ~(1<<PD3);
										break;
								case 5: DDRA |= (1<<PD4);
										DDRD |= (1<<PD3);	
			
										PORTA |= (1<<PD4);
										PORTD &= ~(1<<PD3);
										break;
							}break;
					case 2: switch(z)
							{
								case 1: DDRA |= (1<<PD0);
										DDRD |= (1<<PD4);	
			
										PORTA |= (1<<PD0);
										PORTD &= ~(1<<PD4);
										break;
								case 2: DDRA |= (1<<PD1);
										DDRD |= (1<<PD4);	
			
										PORTA |= (1<<PD1);
										PORTD &= ~(1<<PD4);
										break;
								case 3: DDRA |= (1<<PD2);
										DDRD |= (1<<PD4);	
			
										PORTA |= (1<<PD2);
										PORTD &= ~(1<<PD4);
										break;
								case 4: DDRA |= (1<<PD3);
										DDRD |= (1<<PD4);	
			
										PORTA |= (1<<PD3);
										PORTD &= ~(1<<PD4);
										break;
								case 5: DDRA |= (1<<PD4);
										DDRD |= (1<<PD4);	
			
										PORTA |= (1<<PD4);
										PORTD &= ~(1<<PD4);
										break;
							}break;
					case 3: switch(z)
							{
								case 1: DDRA |= (1<<PD0);
										DDRD |= (1<<PD5);	
			
										PORTA |= (1<<PD0);
										PORTD &= ~(1<<PD5);
										break;
								case 2: DDRA |= (1<<PD1);
										DDRD |= (1<<PD5);	
			
										PORTA |= (1<<PD1);
										PORTD &= ~(1<<PD5);
										break;
								case 3: DDRA |= (1<<PD2);
										DDRD |= (1<<PD5);	
			
										PORTA |= (1<<PD2);
										PORTD &= ~(1<<PD5);
										break;
								case 4: DDRA |= (1<<PD3);
										DDRD |= (1<<PD5);	
			
										PORTA |= (1<<PD3);
										PORTD &= ~(1<<PD5);
										break;
								case 5: DDRA |= (1<<PD4);
										DDRD |= (1<<PD5);	
			
										PORTA |= (1<<PD4);
										PORTD &= ~(1<<PD5);
										break;
							}break;
					case 4: switch(z)
							{
								case 1: DDRA |= (1<<PD0);
										DDRD |= (1<<PD6);	
			
										PORTA |= (1<<PD0);
										PORTD &= ~(1<<PD6);
										break;
								case 2: DDRA |= (1<<PD1);
										DDRD |= (1<<PD6);	
			
										PORTA |= (1<<PD1);
										PORTD &= ~(1<<PD6);
										break;
								case 3: DDRA |= (1<<PD2);
										DDRD |= (1<<PD6);	
			
										PORTA |= (1<<PD2);
										PORTD &= ~(1<<PD6);
										break;
								case 4: DDRA |= (1<<PD3);
										DDRD |= (1<<PD6);	
			
										PORTA |= (1<<PD3);
										PORTD &= ~(1<<PD6);
										break;
								case 5: DDRA |= (1<<PD4);
										DDRD |= (1<<PD6);	
			
										PORTA |= (1<<PD4);
										PORTD &= ~(1<<PD6);
										break;
							}break;	
					case 5: switch(z)
							{
								case 1: DDRA |= (1<<PD0);
										DDRD |= (1<<PD7);	
			
										PORTA |= (1<<PD0);
										PORTD &= ~(1<<PD7);
										break;
								case 2: DDRA |= (1<<PD1);
										DDRD |= (1<<PD7);	
			
										PORTA |= (1<<PD1);
										PORTD &= ~(1<<PD7);
										break;
								case 3: DDRA |= (1<<PD2);
										DDRD |= (1<<PD7);	
			
										PORTA |= (1<<PD2);
										PORTD &= ~(1<<PD7);
										break;
								case 4: DDRA |= (1<<PD3);
										DDRD |= (1<<PD7);	
			
										PORTA |= (1<<PD3);
										PORTD &= ~(1<<PD7);
										break;
								case 5: DDRA |= (1<<PD4);
										DDRD |= (1<<PD7);	
			
										PORTA |= (1<<PD4);
										PORTD &= ~(1<<PD7);
										break;
							}break;
				}break;
				
		case 2: switch(x)
				{
					case 1: switch(z)
							{
								case 1: DDRA |= (1<<PD0);
										DDRD |= (1<<PD3);	
			
										PORTA &= ~(1<<PD0);
										PORTD |= (1<<PD3);
										break;
								case 2: DDRA |= (1<<PD1);
										DDRD |= (1<<PD3);	
			
										PORTA &= ~(1<<PD1);
										PORTD |= (1<<PD3);
										break;
								case 3: DDRA |= (1<<PD2);
										DDRD |= (1<<PD3);	
			
										PORTA &= ~(1<<PD2);
										PORTD |= (1<<PD3);
										break;
								case 4: DDRA |= (1<<PD3);
										DDRD |= (1<<PD3);	
			
										PORTA &= ~(1<<PD3);
										PORTD |= (1<<PD3);
										break;
								case 5: DDRA |= (1<<PD4);
										DDRD |= (1<<PD3);	
			
										PORTA &= ~(1<<PD4);
										PORTD |= (1<<PD3);
										break;
							}break;
					case 2: switch(z)
							{
								case 1: DDRA |= (1<<PD0);
										DDRD |= (1<<PD4);	
			
										PORTA &= ~(1<<PD0);
										PORTD |= (1<<PD4);
										break;
								case 2: DDRA |= (1<<PD1);
										DDRD |= (1<<PD4);	
			
										PORTA &= ~(1<<PD1);
										PORTD |= (1<<PD4);
										break;
								case 3: DDRA |= (1<<PD2);
										DDRD |= (1<<PD4);	
			
										PORTA &= ~(1<<PD2);
										PORTD |= (1<<PD4);
										break;
								case 4: DDRA |= (1<<PD3);
										DDRD |= (1<<PD4);	
			
										PORTA &= ~(1<<PD3);
										PORTD |= (1<<PD4);
										break;
								case 5: DDRA |= (1<<PD4);
										DDRD |= (1<<PD4);	
			
										PORTA &= ~(1<<PD4);
										PORTD |= (1<<PD4);
										break;
							}break;
					case 3: switch(z)
							{
								case 1: DDRA |= (1<<PD0);
										DDRD |= (1<<PD5);	
			
										PORTA &= ~(1<<PD0);
										PORTD |= (1<<PD5);
										break;
								case 2: DDRA |= (1<<PD1);
										DDRD |= (1<<PD5);	
			
										PORTA &= ~(1<<PD1);
										PORTD |= (1<<PD5);
										break;
								case 3: DDRA |= (1<<PD2);
										DDRD |= (1<<PD5);	
			
										PORTA &= ~(1<<PD2);
										PORTD |= (1<<PD5);
										break;
								case 4: DDRA |= (1<<PD3);
										DDRD |= (1<<PD5);	
			
										PORTA &= ~(1<<PD3);
										PORTD |= (1<<PD5);
										break;
								case 5: DDRA |= (1<<PD4);
										DDRD |= (1<<PD5);	
			
										PORTA &= ~(1<<PD4);
										PORTD |= (1<<PD5);
										break;
							}break;
					case 4: switch(z)
							{
								case 1: DDRA |= (1<<PD0);
										DDRD |= (1<<PD6);	
			
										PORTA &= ~(1<<PD0);
										PORTD |= (1<<PD6);
										break;
								case 2: DDRA |= (1<<PD1);
										DDRD |= (1<<PD6);	
			
										PORTA &= ~(1<<PD1);
										PORTD |= (1<<PD6);
										break;
								case 3: DDRA |= (1<<PD2);
										DDRD |= (1<<PD6);	
			
										PORTA &= ~(1<<PD2);
										PORTD |= (1<<PD6);
										break;
								case 4: DDRA |= (1<<PD3);
										DDRD |= (1<<PD6);	
			
										PORTA &= ~(1<<PD3);
										PORTD |= (1<<PD6);
										break;
								case 5: DDRA |= (1<<PD4);
										DDRD |= (1<<PD6);	
			
										PORTA &= ~(1<<PD4);
										PORTD |= (1<<PD6);
										break;
							}break;
					case 5: switch(z)
							{
								case 1: DDRA |= (1<<PD0);
										DDRD |= (1<<PD7);	
			
										PORTA &= ~(1<<PD0);
										PORTD |= (1<<PD7);
										break;
								case 2: DDRA |= (1<<PD1);
										DDRD |= (1<<PD7);	
			
										PORTA &= ~(1<<PD1);
										PORTD |= (1<<PD7);
										break;
								case 3: DDRA |= (1<<PD2);
										DDRD |= (1<<PD7);	
			
										PORTA &= ~(1<<PD2);
										PORTD |= (1<<PD7);
										break;
								case 4: DDRA |= (1<<PD3);
										DDRD |= (1<<PD7);	
			
										PORTA &= ~(1<<PD3);
										PORTD |= (1<<PD7);
										break;
								case 5: DDRA |= (1<<PD4);
										DDRD |= (1<<PD7);	
			
										PORTA &= ~(1<<PD4);
										PORTD |= (1<<PD7);
										break;
							}break;
				}break;
		case 3: switch(x)
				{
					case 1: switch(z)
							{
								case 1: DDRA |= (1<<PD0);
										DDRC |= (1<<PD7);	
			
										PORTA |= (1<<PD0);
										PORTC &= ~(1<<PD7);
										break;
								case 2: DDRA |= (1<<PD1);
										DDRC |= (1<<PD7);	
			
										PORTA |= (1<<PD1);
										PORTC &= ~(1<<PD7);
										break;
								case 3: DDRA |= (1<<PD2);
										DDRC |= (1<<PD7);	
			
										PORTA |= (1<<PD2);
										PORTC &= ~(1<<PD7);
										break;
								case 4: DDRA |= (1<<PD3);
										DDRC |= (1<<PD7);	
			
										PORTA |= (1<<PD3);
										PORTC &= ~(1<<PD7);
										break;
								case 5: DDRA |= (1<<PD4);
										DDRC |= (1<<PD7);	
			
										PORTA |= (1<<PD4);
										PORTC &= ~(1<<PD7);
										break;
							}break;
					case 2: switch(z)
							{
								case 1: DDRA |= (1<<PD0);
										DDRC |= (1<<PD6);	
			
										PORTA |= (1<<PD0);
										PORTC &= ~(1<<PD6);
										break;
								case 2: DDRA |= (1<<PD1);
										DDRC |= (1<<PD6);	
			
										PORTA |= (1<<PD1);
										PORTC &= ~(1<<PD6);
										break;
								case 3: DDRA |= (1<<PD2);
										DDRC |= (1<<PD6);	
			
										PORTA |= (1<<PD2);
										PORTC &= ~(1<<PD6);
										break;
								case 4: DDRA |= (1<<PD3);
										DDRC |= (1<<PD6);	
			
										PORTA |= (1<<PD3);
										PORTC &= ~(1<<PD6);
										break;
								case 5: DDRA |= (1<<PD4);
										DDRC |= (1<<PD6);	
			
										PORTA |= (1<<PD4);
										PORTC &= ~(1<<PD6);
										break;
							}break;
					case 3: switch(z)
							{
								case 1: DDRA |= (1<<PD0);
										DDRC |= (1<<PD3);	
			
										PORTA |= (1<<PD0);
										PORTC &= ~(1<<PD3);
										break;
								case 2: DDRA |= (1<<PD1);
										DDRC |= (1<<PD3);	
			
										PORTA |= (1<<PD1);
										PORTC &= ~(1<<PD3);
										break;
								case 3: DDRA |= (1<<PD2);
										DDRC |= (1<<PD3);	
			
										PORTA |= (1<<PD2);
										PORTC &= ~(1<<PD3);
										break;
								case 4: DDRA |= (1<<PD3);
										DDRC |= (1<<PD3);	
			
										PORTA |= (1<<PD3);
										PORTC &= ~(1<<PD3);
										break;
								case 5: DDRA |= (1<<PD4);
										DDRC |= (1<<PD3);	
			
										PORTA |= (1<<PD4);
										PORTC &= ~(1<<PD3);
										break;
							}break;
					case 4: switch(z)
							{
								case 1: DDRA |= (1<<PD0);
										DDRC |= (1<<PD4);	
			
										PORTA |= (1<<PD0);
										PORTC &= ~(1<<PD4);
										break;
								case 2: DDRA |= (1<<PD1);
										DDRC |= (1<<PD4);	
			
										PORTA |= (1<<PD1);
										PORTC &= ~(1<<PD4);
										break;
								case 3: DDRA |= (1<<PD2);
										DDRC |= (1<<PD4);	
			
										PORTA |= (1<<PD2);
										PORTC &= ~(1<<PD4);
										break;
								case 4: DDRA |= (1<<PD3);
										DDRC |= (1<<PD4);	
			
										PORTA |= (1<<PD3);
										PORTC &= ~(1<<PD4);
										break;
								case 5: DDRA |= (1<<PD4);
										DDRC |= (1<<PD4);	
			
										PORTA |= (1<<PD4);
										PORTC &= ~(1<<PD4);
										break;
							}break;	
					case 5: switch(z)
							{
								case 1: DDRA |= (1<<PD0);
										DDRC |= (1<<PD5);	
			
										PORTA |= (1<<PD0);
										PORTC &= ~(1<<PD5);
										break;
								case 2: DDRA |= (1<<PD1);
										DDRC |= (1<<PD5);	
			
										PORTA |= (1<<PD1);
										PORTC &= ~(1<<PD5);
										break;
								case 3: DDRA |= (1<<PD2);
										DDRC |= (1<<PD5);	
			
										PORTA |= (1<<PD2);
										PORTC &= ~(1<<PD5);
										break;
								case 4: DDRA |= (1<<PD3);
										DDRC |= (1<<PD5);	
			
										PORTA |= (1<<PD3);
										PORTC &= ~(1<<PD5);
										break;
								case 5: DDRA |= (1<<PD4);
										DDRC |= (1<<PD5);	
			
										PORTA |= (1<<PD4);
										PORTC &= ~(1<<PD5);
										break;
							}break;
				}break;
		case 4: switch(x)
				{
				
					case 1: switch(z)
							{
								case 1: DDRA |= (1<<PD0);
										DDRC |= (1<<PD7);	
			
										PORTA &= ~(1<<PD0);
										PORTC |= (1<<PD7);
										break;
								case 2: DDRA |= (1<<PD1);
										DDRC |= (1<<PD7);	
			
										PORTA &= ~(1<<PD1);
										PORTC |= (1<<PD7);
										break;
								case 3: DDRA |= (1<<PD2);
										DDRC |= (1<<PD7);	
			
										PORTA &= ~(1<<PD2);
										PORTC |= (1<<PD7);
										break;
								case 4: DDRA |= (1<<PD3);
										DDRC |= (1<<PD7);	
			
										PORTA &= ~(1<<PD3);
										PORTC |= (1<<PD7);
										break;
								case 5: DDRA |= (1<<PD4);
										DDRC |= (1<<PD7);	
			
										PORTA &= ~(1<<PD4);
										PORTC |= (1<<PD7);
										break;
							}break;
					case 2: switch(z)
							{
								case 1: DDRA |= (1<<PD0);
										DDRC |= (1<<PD6);	
			
										PORTA &= ~(1<<PD0);
										PORTC |= (1<<PD6);
										break;
								case 2: DDRA |= (1<<PD1);
										DDRC |= (1<<PD6);	
			
										PORTA &= ~(1<<PD1);
										PORTC |= (1<<PD6);
										break;
								case 3: DDRA |= (1<<PD2);
										DDRC |= (1<<PD6);	
			
										PORTA &= ~(1<<PD2);
										PORTC |= (1<<PD6);
										break;
								case 4: DDRA |= (1<<PD3);
										DDRC |= (1<<PD6);	
			
										PORTA &= ~(1<<PD3);
										PORTC |= (1<<PD6);
										break;
								case 5: DDRA |= (1<<PD4);
										DDRC |= (1<<PD6);	
			
										PORTA &= ~(1<<PD4);
										PORTC |= (1<<PD6);
										break;
							}break;
					case 3: switch(z)
							{
								case 1: DDRA |= (1<<PD0);
										DDRC |= (1<<PD3);	
			
										PORTA &= ~(1<<PD0);
										PORTC |= (1<<PD3);
										break;
								case 2: DDRA |= (1<<PD1);
										DDRC |= (1<<PD3);	
			
										PORTA &= ~(1<<PD1);
										PORTC |= (1<<PD3);
										break;
								case 3: DDRA |= (1<<PD2);
										DDRC |= (1<<PD3);	
			
										PORTA &= ~(1<<PD2);
										PORTC |= (1<<PD3);
										break;
								case 4: DDRA |= (1<<PD3);
										DDRC |= (1<<PD3);	
			
										PORTA &= ~(1<<PD3);
										PORTC |= (1<<PD3);
										break;
								case 5: DDRA |= (1<<PD4);
										DDRC |= (1<<PD3);	
			
										PORTA &= ~(1<<PD4);
										PORTC |= (1<<PD3);
										break;
							}break;
					case 4: switch(z)
							{
								case 1: DDRA |= (1<<PD0);
										DDRC |= (1<<PD4);	
			
										PORTA &= ~(1<<PD0);
										PORTC |= (1<<PD4);
										break;
								case 2: DDRA |= (1<<PD1);
										DDRC |= (1<<PD4);	
			
										PORTA &= ~(1<<PD1);
										PORTC |= (1<<PD4);
										break;
								case 3: DDRA |= (1<<PD2);
										DDRC |= (1<<PD4);	
			
										PORTA &= ~(1<<PD2);
										PORTC |= (1<<PD4);
										break;
								case 4: DDRA |= (1<<PD3);
										DDRC |= (1<<PD4);	
			
										PORTA &= ~(1<<PD3);
										PORTC |= (1<<PD4);
										break;
								case 5: DDRA |= (1<<PD4);
										DDRC |= (1<<PD4);	
			
										PORTA &= ~(1<<PD4);
										PORTC |= (1<<PD4);
										break;
							}break;
					case 5: switch(z)
							{
								case 1: DDRA |= (1<<PD0);
										DDRC |= (1<<PD5);	
			
										PORTA &= ~(1<<PD0);
										PORTC |= (1<<PD5);
										break;
								case 2: DDRA |= (1<<PD1);
										DDRC |= (1<<PD5);	
			
										PORTA &= ~(1<<PD1);
										PORTC |= (1<<PD5);
										break;
								case 3: DDRA |= (1<<PD2);
										DDRC |= (1<<PD5);	
			
										PORTA &= ~(1<<PD2);
										PORTC |= (1<<PD5);
										break;
								case 4: DDRA |= (1<<PD3);
										DDRC |= (1<<PD5);	
			
										PORTA &= ~(1<<PD3);
										PORTC |= (1<<PD5);
										break;
								case 5: DDRA |= (1<<PD4);
										DDRC |= (1<<PD5);	
			
										PORTA &= ~(1<<PD4);
										PORTC |= (1<<PD5);
										break;
							}break;
				}break;
		case 5: switch(x)
				{
					case 1: switch(z)
							{
								case 1: DDRA |= (1<<PD0);
										DDRB |= (1<<PD4);	
			
										PORTA |= (1<<PD0);
										PORTB &= ~(1<<PD4);
										break;
								case 2: DDRA |= (1<<PD1);
										DDRB |= (1<<PD4);	
			
										PORTA |= (1<<PD1);
										PORTB &= ~(1<<PD4);
										break;
								case 3: DDRA |= (1<<PD2);
										DDRB |= (1<<PD4);	
			
										PORTA |= (1<<PD2);
										PORTB &= ~(1<<PD4);
										break;
								case 4: DDRA |= (1<<PD3);
										DDRB |= (1<<PD4);	
			
										PORTA |= (1<<PD3);
										PORTB &= ~(1<<PD4);
										break;
								case 5: DDRA |= (1<<PD4);
										DDRB |= (1<<PD4);	
			
										PORTA |= (1<<PD4);
										PORTB &= ~(1<<PD4);
										break;
							}break;
					case 2: switch(z)
							{
								case 1: DDRA |= (1<<PD0);
										DDRB |= (1<<PD3);	
			
										PORTA |= (1<<PD0);
										PORTB &= ~(1<<PD3);
										break;
								case 2: DDRA |= (1<<PD1);
										DDRB |= (1<<PD3);	
			
										PORTA |= (1<<PD1);
										PORTB &= ~(1<<PD3);
										break;
								case 3: DDRA |= (1<<PD2);
										DDRB |= (1<<PD3);	
			
										PORTA |= (1<<PD2);
										PORTB &= ~(1<<PD3);
										break;
								case 4: DDRA |= (1<<PD3);
										DDRB |= (1<<PD3);	
			
										PORTA |= (1<<PD3);
										PORTB &= ~(1<<PD3);
										break;
								case 5: DDRA |= (1<<PD4);
										DDRB |= (1<<PD3);	
			
										PORTA |= (1<<PD4);
										PORTB &= ~(1<<PD3);
										break;
							}break;
					case 3: switch(z)
							{
								case 1: DDRA |= (1<<PD0);
										DDRB |= (1<<PD2);	
			
										PORTA |= (1<<PD0);
										PORTB &= ~(1<<PD2);
										break;
								case 2: DDRA |= (1<<PD1);
										DDRB |= (1<<PD2);	
			
										PORTA |= (1<<PD1);
										PORTB &= ~(1<<PD2);
										break;
								case 3: DDRA |= (1<<PD2);
										DDRB |= (1<<PD2);	
			
										PORTA |= (1<<PD2);
										PORTB &= ~(1<<PD2);
										break;
								case 4: DDRA |= (1<<PD3);
										DDRB |= (1<<PD2);	
			
										PORTA |= (1<<PD3);
										PORTB &= ~(1<<PD2);
										break;
								case 5: DDRA |= (1<<PD4);
										DDRB |= (1<<PD2);	
			
										PORTA |= (1<<PD4);
										PORTB &= ~(1<<PD2);
										break;
							}break;
					case 4: switch(z)
							{
								case 1: DDRA |= (1<<PD0);
										DDRB |= (1<<PD1);	
			
										PORTA |= (1<<PD0);
										PORTB &= ~(1<<PD1);
										break;
								case 2: DDRA |= (1<<PD1);
										DDRB |= (1<<PD1);	
			
										PORTA |= (1<<PD1);
										PORTB &= ~(1<<PD1);
										break;
								case 3: DDRA |= (1<<PD2);
										DDRB |= (1<<PD1);	
			
										PORTA |= (1<<PD2);
										PORTB &= ~(1<<PD1);
										break;
								case 4: DDRA |= (1<<PD3);
										DDRB |= (1<<PD1);	
			
										PORTA |= (1<<PD3);
										PORTB &= ~(1<<PD1);
										break;
								case 5: DDRA |= (1<<PD4);
										DDRB |= (1<<PD1);	
			
										PORTA |= (1<<PD4);
										PORTB &= ~(1<<PD1);
										break;
							}break;	
					case 5: switch(z)
							{
								case 1: DDRA |= (1<<PD0);
										DDRB |= (1<<PD0);	
			
										PORTA |= (1<<PD0);
										PORTB &= ~(1<<PD0);
										break;
								case 2: DDRA |= (1<<PD1);
										DDRB |= (1<<PD0);	
			
										PORTA |= (1<<PD1);
										PORTB &= ~(1<<PD0);
										break;
								case 3: DDRA |= (1<<PD2);
										DDRB |= (1<<PD0);	
			
										PORTA |= (1<<PD2);
										PORTB &= ~(1<<PD0);
										break;
								case 4: DDRA |= (1<<PD3);
										DDRB |= (1<<PD0);	
			
										PORTA |= (1<<PD3);
										PORTB &= ~(1<<PD0);
										break;
								case 5: DDRA |= (1<<PD4);
										DDRB |= (1<<PD0);	
			
										PORTA |= (1<<PD4);
										PORTB &= ~(1<<PD0);
										break;
							}break;
				}break;
	}
}

void senk( short x, short z)
{
	DDRA = 0x00;
	DDRB = 0x00;
	DDRC = 0x00;
	DDRD = 0x00;
	
	short s = 1;
	
	switch(x)
	{
		case 1:switch(z)
				{
					case 1:	led(1,1,1);
							_delay_ms(s);
							led(2,1,1);
							_delay_ms(s);
							led(3,1,1);
							_delay_ms(s);
							led(4,1,1);
							_delay_ms(s);
							led(5,1,1);
							_delay_ms(s);
							break;		
					case 2: led(1,1,2);
							_delay_ms(s);
							led(2,1,2);
							_delay_ms(s);
							led(3,1,2);
							_delay_ms(s);
							led(4,1,2);
							_delay_ms(s);
							led(5,1,2);
							_delay_ms(s);
							break;
					case 3: led(1,1,3);
							_delay_ms(s);
							led(2,1,3);
							_delay_ms(s);
							led(3,1,3);
							_delay_ms(s);
							led(4,1,3);
							_delay_ms(s);
							led(5,1,3);
							_delay_ms(s);
							break;
					case 4: led(1,1,4);
							_delay_ms(s);
							led(2,1,4);
							_delay_ms(s);
							led(3,1,4);
							_delay_ms(s);
							led(4,1,4);
							_delay_ms(s);
							led(5,1,4);
							_delay_ms(s);
							break;
					case 5:	led(1,1,5);
							_delay_ms(s);
							led(2,1,5);
							_delay_ms(s);
							led(3,1,5);
							_delay_ms(s);
							led(4,1,5);
							_delay_ms(s);
							led(5,1,5);
							_delay_ms(s);
							break;
				}break;
		case 2:switch(z)
				{
					case 1:	led(1,2,1);
							_delay_ms(s);
							led(2,2,1);
							_delay_ms(s);
							led(3,2,1);
							_delay_ms(s);
							led(4,2,1);
							_delay_ms(s);
							led(5,2,1);
							_delay_ms(s);
							break;		
					case 2: led(1,2,2);
							_delay_ms(s);
							led(2,2,2);
							_delay_ms(s);
							led(3,2,2);
							_delay_ms(s);
							led(4,2,2);
							_delay_ms(s);
							led(5,2,2);
							_delay_ms(s);
							break;
					case 3: led(1,2,3);
							_delay_ms(s);
							led(2,2,3);
							_delay_ms(s);
							led(3,2,3);
							_delay_ms(s);
							led(4,2,3);
							_delay_ms(s);
							led(5,2,3);
							_delay_ms(s);
							break;
					case 4: led(1,2,4);
							_delay_ms(s);
							led(2,2,4);
							_delay_ms(s);
							led(3,2,4);
							_delay_ms(s);
							led(4,2,4);
							_delay_ms(s);
							led(5,2,4);
							_delay_ms(s);
							break;
					case 5:	led(1,2,5);
							_delay_ms(s);
							led(2,2,5);
							_delay_ms(s);
							led(3,2,5);
							_delay_ms(s);
							led(4,2,5);
							_delay_ms(s);
							led(5,2,5);
							_delay_ms(s);
							break;
				}break;
		case 3:switch(z)
				{
					case 1:	led(1,3,1);
							_delay_ms(s);
							led(2,3,1);
							_delay_ms(s);
							led(3,3,1);
							_delay_ms(s);
							led(4,3,1);
							_delay_ms(s);
							led(5,3,1);
							_delay_ms(s);
							break;		
					case 2: led(1,3,2);
							_delay_ms(s);
							led(2,3,2);
							_delay_ms(s);
							led(3,3,2);
							_delay_ms(s);
							led(4,3,2);
							_delay_ms(s);
							led(5,3,2);
							_delay_ms(s);
							break;
					case 3: led(1,3,3);
							_delay_ms(s);
							led(2,3,3);
							_delay_ms(s);
							led(3,3,3);
							_delay_ms(s);
							led(4,3,3);
							_delay_ms(s);
							led(5,3,3);
							_delay_ms(s);
							break;
					case 4: led(1,3,4);
							_delay_ms(s);
							led(2,3,4);
							_delay_ms(s);
							led(3,3,4);
							_delay_ms(s);
							led(4,3,4);
							_delay_ms(s);
							led(5,3,4);
							_delay_ms(s);
							break;
					case 5:	led(1,3,5);
							_delay_ms(s);
							led(2,3,5);
							_delay_ms(s);
							led(3,3,5);
							_delay_ms(s);
							led(4,3,5);
							_delay_ms(s);
							led(5,3,5);
							_delay_ms(s);
							break;
				}break;
		case 4:switch(z)
				{
					case 1:	led(1,4,1);
							_delay_ms(s);
							led(2,4,1);
							_delay_ms(s);
							led(3,4,1);
							_delay_ms(s);
							led(4,4,1);
							_delay_ms(s);
							led(5,4,1);
							_delay_ms(s);
							break;		
					case 2: led(1,4,2);
							_delay_ms(s);
							led(2,4,2);
							_delay_ms(s);
							led(3,4,2);
							_delay_ms(s);
							led(4,4,2);
							_delay_ms(s);
							led(5,4,2);
							_delay_ms(s);
							break;
					case 3: led(1,4,3);
							_delay_ms(s);
							led(2,4,3);
							_delay_ms(s);
							led(3,4,3);
							_delay_ms(s);
							led(4,4,3);
							_delay_ms(s);
							led(5,4,3);
							_delay_ms(s);
							break;
					case 4: led(1,4,4);
							_delay_ms(s);
							led(2,4,4);
							_delay_ms(s);
							led(3,4,4);
							_delay_ms(s);
							led(4,4,4);
							_delay_ms(s);
							led(5,4,4);
							_delay_ms(s);
							break;
					case 5:	led(1,4,5);
							_delay_ms(s);
							led(2,4,5);
							_delay_ms(s);
							led(3,4,5);
							_delay_ms(s);
							led(4,4,5);
							_delay_ms(s);
							led(5,4,5);
							_delay_ms(s);
							break;
				}break;
		case 5:switch(z)
				{
					case 1:	led(1,5,1);
							_delay_ms(s);
							led(2,5,1);
							_delay_ms(s);
							led(3,5,1);
							_delay_ms(s);
							led(4,5,1);
							_delay_ms(s);
							led(5,5,1);
							_delay_ms(s);
							break;		
					case 2: led(1,5,2);
							_delay_ms(s);
							led(2,5,2);
							_delay_ms(s);
							led(3,5,2);
							_delay_ms(s);
							led(4,5,2);
							_delay_ms(s);
							led(5,5,2);
							_delay_ms(s);
							break;
					case 3: led(1,5,3);
							_delay_ms(s);
							led(2,5,3);
							_delay_ms(s);
							led(3,5,3);
							_delay_ms(s);
							led(4,5,3);
							_delay_ms(s);
							led(5,5,3);
							_delay_ms(s);
							break;
					case 4: led(1,5,4);
							_delay_ms(s);
							led(2,5,4);
							_delay_ms(s);
							led(3,5,4);
							_delay_ms(s);
							led(4,5,4);
							_delay_ms(s);
							led(5,5,4);
							_delay_ms(s);
							break;
					case 5:	led(1,5,5);
							_delay_ms(s);
							led(2,5,5);
							_delay_ms(s);
							led(3,5,5);
							_delay_ms(s);
							led(4,5,5);
							_delay_ms(s);
							led(5,5,5);
							_delay_ms(s);
							break;
				}break;
	}
	
}


void wag(short y, short z)
{

	short s = 1;
	
	switch(y)
	{ 
		case 1: switch(z)
				{
				case 1:	led(1,1,1);
						_delay_ms(s);
						led(1,2,1);
						_delay_ms(s);
						led(1,3,1);
						_delay_ms(s);
						led(1,4,1);
						_delay_ms(s);
						led(1,5,1);
						_delay_ms(s);
						break;	
				case 2:	led(1,1,2);
						_delay_ms(s);
						led(1,2,2);
						_delay_ms(s);
						led(1,3,2);
						_delay_ms(s);
						led(1,4,2);
						_delay_ms(s);
						led(1,5,2);
						_delay_ms(s);
						break;	
				case 3:	led(1,1,3);
						_delay_ms(s);
						led(1,2,3);
						_delay_ms(s);
						led(1,3,3);
						_delay_ms(s);
						led(1,4,3);
						_delay_ms(s);
						led(1,5,3);
						_delay_ms(s);
						break;	
				case 4:	led(1,1,4);
						_delay_ms(s);
						led(1,2,4);
						_delay_ms(s);
						led(1,3,4);
						_delay_ms(s);
						led(1,4,4);
						_delay_ms(s);
						led(1,5,4);
						_delay_ms(s);
						break;	
				case 5:	led(1,1,5);
						_delay_ms(s);
						led(1,2,5);
						_delay_ms(s);
						led(1,3,5);
						_delay_ms(s);
						led(1,4,5);
						_delay_ms(s);
						led(1,5,5);
						_delay_ms(s);
						break;
				}break;
		case 2: switch(z)
				{
				case 1:	led(2,1,1);
						_delay_ms(s);
						led(2,2,1);
						_delay_ms(s);
						led(2,3,1);
						_delay_ms(s);
						led(2,4,1);
						_delay_ms(s);
						led(2,5,1);
						_delay_ms(s);
						break;	
				case 2:	led(2,1,2);
						_delay_ms(s);
						led(2,2,2);
						_delay_ms(s);
						led(2,3,2);
						_delay_ms(s);
						led(2,4,2);
						_delay_ms(s);
						led(2,5,2);
						_delay_ms(s);
						break;	
				case 3:	led(2,1,3);
						_delay_ms(s);
						led(2,2,3);
						_delay_ms(s);
						led(2,3,3);
						_delay_ms(s);
						led(2,4,3);
						_delay_ms(s);
						led(2,5,3);
						_delay_ms(s);
						break;	
				case 4:	led(2,1,4);
						_delay_ms(s);
						led(2,2,4);
						_delay_ms(s);
						led(2,3,4);
						_delay_ms(s);
						led(2,4,4);
						_delay_ms(s);
						led(2,5,4);
						_delay_ms(s);
						break;	
				case 5:	led(2,1,5);
						_delay_ms(s);
						led(2,2,5);
						_delay_ms(s);
						led(2,3,5);
						_delay_ms(s);
						led(2,4,5);
						_delay_ms(s);
						led(2,5,5);
						_delay_ms(s);
						break;
				}break;	
		case 3: switch(z)
				{
				case 1:	led(3,1,1);
						_delay_ms(s);
						led(3,2,1);
						_delay_ms(s);
						led(3,3,1);
						_delay_ms(s);
						led(3,4,1);
						_delay_ms(s);
						led(3,5,1);
						_delay_ms(s);
						break;	
				case 2:	led(3,1,2);
						_delay_ms(s);
						led(3,2,2);
						_delay_ms(s);
						led(3,3,2);
						_delay_ms(s);
						led(3,4,2);
						_delay_ms(s);
						led(3,5,2);
						_delay_ms(s);
						break;	
				case 3:	led(3,1,3);
						_delay_ms(s);
						led(3,2,3);
						_delay_ms(s);
						led(3,3,3);
						_delay_ms(s);
						led(3,4,3);
						_delay_ms(s);
						led(3,5,3);
						_delay_ms(s);
						break;	
				case 4:	led(3,1,4);
						_delay_ms(s);
						led(3,2,4);
						_delay_ms(s);
						led(3,3,4);
						_delay_ms(s);
						led(3,4,4);
						_delay_ms(s);
						led(3,5,4);
						_delay_ms(s);
						break;	
				case 5:	led(3,1,5);
						_delay_ms(s);
						led(3,2,5);
						_delay_ms(s);
						led(3,3,5);
						_delay_ms(s);
						led(3,4,5);
						_delay_ms(s);
						led(3,5,5);
						_delay_ms(s);
						break;
				}break;	
		case 4: switch(z)
				{
				case 1:	led(4,1,1);
						_delay_ms(s);
						led(4,2,1);
						_delay_ms(s);
						led(4,3,1);
						_delay_ms(s);
						led(4,4,1);
						_delay_ms(s);
						led(4,5,1);
						_delay_ms(s);
						break;	
				case 2:	led(4,1,2);
						_delay_ms(s);
						led(4,2,2);
						_delay_ms(s);
						led(4,3,2);
						_delay_ms(s);
						led(4,4,2);
						_delay_ms(s);
						led(4,5,2);
						_delay_ms(s);
						break;	
				case 3:	led(4,1,3);
						_delay_ms(s);
						led(4,2,3);
						_delay_ms(s);
						led(4,3,3);
						_delay_ms(s);
						led(4,4,3);
						_delay_ms(s);
						led(4,5,3);
						_delay_ms(s);
						break;	
				case 4:	led(4,1,4);
						_delay_ms(s);
						led(4,2,4);
						_delay_ms(s);
						led(4,3,4);
						_delay_ms(s);
						led(4,4,4);
						_delay_ms(s);
						led(4,5,4);
						_delay_ms(s);
						break;	
				case 5:	led(4,1,5);
						_delay_ms(s);
						led(4,2,5);
						_delay_ms(s);
						led(4,3,5);
						_delay_ms(s);
						led(4,4,5);
						_delay_ms(s);
						led(4,5,5);
						_delay_ms(s);
						break;
				}break;	
		case 5: switch(z)
				{
				case 1:	led(5,1,1);
						_delay_ms(s);
						led(5,2,1);
						_delay_ms(s);
						led(5,3,1);
						_delay_ms(s);
						led(5,4,1);
						_delay_ms(s);
						led(5,5,1);
						_delay_ms(s);
						break;	
				case 2:	led(5,1,2);
						_delay_ms(s);
						led(5,2,2);
						_delay_ms(s);
						led(5,3,2);
						_delay_ms(s);
						led(5,4,2);
						_delay_ms(s);
						led(5,5,2);
						_delay_ms(s);
						break;	
				case 3:	led(5,1,3);
						_delay_ms(s);
						led(5,2,3);
						_delay_ms(s);
						led(5,3,3);
						_delay_ms(s);
						led(5,4,3);
						_delay_ms(s);
						led(5,5,3);
						_delay_ms(s);
						break;	
				case 4:	led(5,1,4);
						_delay_ms(s);
						led(5,2,4);
						_delay_ms(s);
						led(5,3,4);
						_delay_ms(s);
						led(5,4,4);
						_delay_ms(s);
						led(5,5,4);
						_delay_ms(s);
						break;	
				case 5:	led(5,1,5);
						_delay_ms(s);
						led(5,2,5);
						_delay_ms(s);
						led(5,3,5);
						_delay_ms(s);
						led(5,4,5);
						_delay_ms(s);
						led(5,5,5);
						_delay_ms(s);
						break;
				}break;	
	}
}



int main(void)
{
	ms = 0;
	ms10 = 0;
	ms100= 0;
	sec = 0;
	
	
	TCCR1A = 0;					// Timer1: keine PWM

    // Timer1 ist Zähler: Clear Timer on Compare Match (CTC, Mode #4)
    // Timer1 läuft mit vollem MCU-Takt: Prescale = 1
	#if defined (CTC1) && !defined (WGM12)
   TCCR1B = (1 << CTC1)  | (1 << CS10);
	#elif !defined (CTC1) && defined (WGM12)
   TCCR1B = (1 << WGM12) | (1 << CS10);
	#else
	#error Keine Ahnung!
	#endif

    // OutputCompare für gewünschte Timer1 Frequenz
    // TCNT1 zählt immer 0...OCR1A, 0...OCR1A, ... 
    // Beim überlauf OCR1A -> OCR1A+1 wird TCNT1=0 gesetzt und im nächsten
    // MCU-Takt eine IRQ erzeugt.
    OCR1A = (unsigned short) ((unsigned long) F_CPU / IRQS_PER_SECOND-1);

    // OutputCompareA-Interrupt für Timer1 aktivieren
	#if defined (TIMSK1)
    TIMSK1 |= (1 << OCIE1A);
	#elif defined (TIMSK)
    TIMSK  |= (1 << OCIE1A);
	#else
	#error Keine Ahnung!
	#endif
	sei();
		
		
		//short bremse = 1;
		//short bremsel = 3;
		
	/*while(1)
	{
		
		while(up <= 1)// Fläche 1 leuchtet
		{
		wag(1,1);
		wag(1,2);
		wag(1,3);
		wag(1,4);
		wag(1,5);
		}
		
		while(up <= 3)// Fläche 2 leuchtet
		{
		wag(2,1);
		wag(2,2);
		wag(2,3);
		wag(2,4);
		wag(2,5);
		}
		
		while(up <= 5)// Fläche 3 leuchtet
		{
		wag(3,1);
		wag(3,2);
		wag(3,3);
		wag(3,4);
		wag(3,5);
		}
		
		while(up <= 7)// Fläche 4 leuchtet
		{
		wag(4,1);
		wag(4,2);
		wag(4,3);
		wag(4,4);
		wag(4,5);
		}
		
		while(up <= 9)// Fläche 5 leuchtet
		{
		wag(5,1);
		wag(5,2);
		wag(5,3);
		wag(5,4);
		wag(5,5);
		}
		
		
		while(up <= 11)// Die 4 äusersten Ebene 5
		{
		led(5,1,5);
		_delay_ms(bremse);
		led(5,1,1);
		_delay_ms(bremse);
		led(5,5,1);
		_delay_ms(bremse);
		led(5,5,5);
		_delay_ms(bremse);
		}
		
		while(up <= 12)// Die 4 äusersten Ebene 4
		{
		led(4,1,5);
		_delay_ms(bremse);
		led(4,1,1);
		_delay_ms(bremse);
		led(4,5,1);
		_delay_ms(bremse);
		led(4,5,5);
		_delay_ms(bremse);
		}
		
		while(up <= 13)// Die 4 äusersten Ebene 3
		{
		led(3,1,5);
		_delay_ms(bremse);
		led(3,1,1);
		_delay_ms(bremse);
		led(3,5,1);
		_delay_ms(bremse);
		led(3,5,5);
		_delay_ms(bremse);
		}
		
		while(up <= 14)// Die 4 äusersten Ebene 2
		{
		led(2,1,5);
		_delay_ms(bremse);
		led(2,1,1);
		_delay_ms(bremse);
		led(2,5,1);
		_delay_ms(bremse);
		led(2,5,5);
		_delay_ms(bremse);
		}
		
		while(up <= 15)// Die 4 äusersten Ebene 1
		{
		led(1,1,5);
		_delay_ms(bremse);
		led(1,1,1);
		_delay_ms(bremse);
		led(1,5,1);
		_delay_ms(bremse);
		led(1,5,5);
		_delay_ms(bremse);
		}
		
		while(up <= 16)// Die 4 mittleren äusersten Ebene 1
		{
		led(1,2,2);
		_delay_ms(bremse);
		led(1,2,4);
		_delay_ms(bremse);
		led(1,4,2);
		_delay_ms(bremse);
		led(1,4,4);
		_delay_ms(bremse);
		}
		
		while(up <= 18)// Die mittigste Ebene 1
		{
		led(1,3,3);
		}
		
		while(up <= 19)// Die mittigste Ebene 2
		{
		led(1,3,3);
		_delay_ms(bremsel);
		led(2,3,3);
		_delay_ms(bremsel);
		}
		
		while(up <= 20)// Die mittigste Ebene 3
		{
		led(1,3,3);
		_delay_ms(bremsel);
		led(2,3,3);
		_delay_ms(bremsel);
		led(3,3,3);
		_delay_ms(bremsel);
		}
		
		while(up <= 21)// Die mittigste Ebene 4
		{
		led(1,3,3);
		_delay_ms(bremsel);
		led(2,3,3);
		_delay_ms(bremsel);
		led(3,3,3);
		_delay_ms(bremsel);
		led(4,3,3);
		_delay_ms(bremsel);
		}
		
		while(up <= 22)// Die mittigste Ebene 5
		{
		led(1,3,3);
		_delay_ms(bremsel);
		led(2,3,3);
		_delay_ms(bremsel);
		led(3,3,3);
		_delay_ms(bremsel);
		led(4,3,3);
		_delay_ms(bremsel);
		led(5,3,3);
		_delay_ms(bremsel);
		}
		
		while(up <= 24)// Die 9 mittleren innersten Ebene 5
		{
		led(1,3,3);
		_delay_ms(bremsel);
		led(2,3,3);
		_delay_ms(bremsel);
		led(3,3,3);
		_delay_ms(bremsel);
		led(4,3,3);
		_delay_ms(bremsel);
		led(5,3,3);
		_delay_ms(bremsel);
		
		led(5,3,3);
		_delay_ms(bremse);
		led(5,2,2);
		_delay_ms(bremse);
		led(5,2,3);
		_delay_ms(bremse);
		led(5,2,4);
		_delay_ms(bremse);
		led(5,3,4);
		_delay_ms(bremse);
		led(5,4,4);
		_delay_ms(bremse);
		led(5,4,3);
		_delay_ms(bremse);
		led(5,4,2);
		_delay_ms(bremse);
		led(5,3,2);
		_delay_ms(bremse);
		}
		
		while(up <= 26 )// Die 9 mittleren innersten Ebene 5 + jedes 2 von aussen
		{
		led(1,3,3);
		_delay_ms(bremsel);
		led(2,3,3);
		_delay_ms(bremsel);
		led(3,3,3);
		_delay_ms(bremsel);
		led(4,3,3);
		_delay_ms(bremsel);
		led(5,3,3);
		_delay_ms(bremsel);
		
		led(5,3,3);
		_delay_ms(bremse);
		led(5,2,2);
		_delay_ms(bremse);
		led(5,2,3);
		_delay_ms(bremse);
		led(5,2,4);
		_delay_ms(bremse);
		led(5,3,4);
		_delay_ms(bremse);
		led(5,4,4);
		_delay_ms(bremse);
		led(5,4,3);
		_delay_ms(bremse);
		led(5,4,2);
		_delay_ms(bremse);
		led(5,3,2);
		_delay_ms(bremse);
		
		led(5,2,5);
		_delay_ms(bremse);
		led(5,4,5);
		_delay_ms(bremse);
		led(5,5,4);
		_delay_ms(bremse);
		_delay_ms(bremse);
		led(5,5,2);
		_delay_ms(bremse);
		led(5,4,1);
		_delay_ms(bremse);
		led(5,2,1);
		_delay_ms(bremse);
		led(5,1,2);
		_delay_ms(bremse);
		led(5,1,4);
		_delay_ms(bremse);
		}
		
		while(up <= 28 )// Die 9 mittleren innersten Ebene 5 + jedes 2 von aussen first drop
		{
		led(1,3,3);
		_delay_ms(bremsel);
		led(2,3,3);
		_delay_ms(bremsel);
		led(3,3,3);
		_delay_ms(bremsel);
		led(4,3,3);
		_delay_ms(bremsel);
		led(5,3,3);
		_delay_ms(bremsel);
		
		led(5,3,3);
		_delay_ms(bremse);
		led(5,2,2);
		_delay_ms(bremse);
		led(5,2,3);
		_delay_ms(bremse);
		led(5,2,4);
		_delay_ms(bremse);
		led(5,3,4);
		_delay_ms(bremse);
		led(5,4,4);
		_delay_ms(bremse);
		led(5,4,3);
		_delay_ms(bremse);
		led(5,4,2);
		_delay_ms(bremse);
		led(5,3,2);
		_delay_ms(bremse);
			
		led(5,2,5);
		_delay_ms(bremse);
		led(5,4,5);
		_delay_ms(bremse);
		led(5,5,4);
		_delay_ms(bremse);
		led(5,5,2);
		_delay_ms(bremse);
		led(5,4,1);
		_delay_ms(bremse);
		led(5,2,1);
		_delay_ms(bremse);
		led(5,1,2);
		_delay_ms(bremse);
		led(5,1,4);
		_delay_ms(bremse);
	
		led(4,2,1);
		_delay_ms(bremse);
		led(4,5,2);
		_delay_ms(bremse);
		led(4,4,5);
		_delay_ms(bremse);
		led(4,1,4);
		_delay_ms(bremse);
		led(5,3,1);
		_delay_ms(bremse);
		led(5,5,3);
		_delay_ms(bremse);
		led(5,3,5);
		_delay_ms(bremse);
		led(5,1,3);
		_delay_ms(bremse);
		}
		
		while(up <= 30)// Die 9 mittleren innersten Ebene 5 + jedes 2 von aussen second drop
		{
		led(1,3,3);
		_delay_ms(bremsel);
		led(2,3,3);
		_delay_ms(bremsel);
		led(3,3,3);
		_delay_ms(bremsel);
		led(4,3,3);
		_delay_ms(bremsel);
		led(5,3,3);
		_delay_ms(bremsel);
		
		led(5,3,3);
		_delay_ms(bremse);
		led(5,2,2);
		_delay_ms(bremse);
		led(5,2,3);
		_delay_ms(bremse);
		led(5,2,4);
		_delay_ms(bremse);
		led(5,3,4);
		_delay_ms(bremse);
		led(5,4,4);
		_delay_ms(bremse);
		led(5,4,3);
		_delay_ms(bremse);
		led(5,4,2);
		_delay_ms(bremse);
		led(5,3,2);
		_delay_ms(bremse);
			
		led(5,2,5);
		_delay_ms(bremse);
		led(5,4,5);
		_delay_ms(bremse);
		led(5,5,4);
		_delay_ms(bremse);
		led(5,5,2);
		_delay_ms(bremse);
		led(5,4,1);
		_delay_ms(bremse);
		led(5,2,1);
		_delay_ms(bremse);
		led(5,1,2);
		_delay_ms(bremse);
		led(5,1,4);
		_delay_ms(bremse);
	
		led(4,2,1);
		_delay_ms(bremse);
		led(4,5,2);
		_delay_ms(bremse);
		led(4,4,5);
		_delay_ms(bremse);
		led(4,1,4);
		_delay_ms(bremse);
		led(5,3,1);
		_delay_ms(bremse);
		led(5,5,3);
		_delay_ms(bremse);
		led(5,3,5);
		_delay_ms(bremse);
		led(5,1,3);
		_delay_ms(bremse);
		
		led(5,4,1);
		_delay_ms(bremse);
		led(5,5,4);
		_delay_ms(bremse);
		led(5,2,5);
		_delay_ms(bremse);
		led(5,1,2);
		_delay_ms(bremse);
		led(4,4,1);
		_delay_ms(bremse);
		led(4,5,4);
		_delay_ms(bremse);
		led(4,2,5);
		_delay_ms(bremse);
		led(4,1,2);
		_delay_ms(bremse);
		
		led(3,2,1);
		_delay_ms(bremse);
		led(3,5,2);
		_delay_ms(bremse);
		led(3,4,5);
		_delay_ms(bremse);
		led(3,1,4);
		_delay_ms(bremse);
		led(4,3,1);
		_delay_ms(bremse);
		led(4,5,3);
		_delay_ms(bremse);
		led(4,3,5);
		_delay_ms(bremse);
		led(4,1,3);
		_delay_ms(bremse);
		}
		
		while(up <= 32)// Die 9 mittleren innersten Ebene 5 + jedes 2 von aussen third drop
		{
		led(1,3,3);
		_delay_ms(bremsel);
		led(2,3,3);
		_delay_ms(bremsel);
		led(3,3,3);
		_delay_ms(bremsel);
		led(4,3,3);
		_delay_ms(bremsel);
		led(5,3,3);
		_delay_ms(bremsel);
		
		led(5,3,3);
		_delay_ms(bremse);
		led(5,2,2);
		_delay_ms(bremse);
		led(5,2,3);
		_delay_ms(bremse);
		led(5,2,4);
		_delay_ms(bremse);
		led(5,3,4);
		_delay_ms(bremse);
		led(5,4,4);
		_delay_ms(bremse);
		led(5,4,3);
		_delay_ms(bremse);
		led(5,4,2);
		_delay_ms(bremse);
		led(5,3,2);
		_delay_ms(bremse);
			
		led(5,2,5);
		_delay_ms(bremse);
		led(5,4,5);
		_delay_ms(bremse);
		led(5,5,4);
		_delay_ms(bremse);
		led(5,5,2);
		_delay_ms(bremse);
		led(5,4,1);
		_delay_ms(bremse);
		led(5,2,1);
		_delay_ms(bremse);
		led(5,1,2);
		_delay_ms(bremse);
		led(5,1,4);
		_delay_ms(bremse);
	
		led(4,2,1);
		_delay_ms(bremse);
		led(4,5,2);
		_delay_ms(bremse);
		led(4,4,5);
		_delay_ms(bremse);
		led(4,1,4);
		_delay_ms(bremse);
		led(5,3,1);
		_delay_ms(bremse);
		led(5,5,3);
		_delay_ms(bremse);
		led(5,3,5);
		_delay_ms(bremse);
		led(5,1,3);
		_delay_ms(bremse);
		
		led(5,4,1);
		_delay_ms(bremse);
		led(5,5,4);
		_delay_ms(bremse);
		led(5,2,5);
		_delay_ms(bremse);
		led(5,1,2);
		_delay_ms(bremse);
		led(4,4,1);
		_delay_ms(bremse);
		led(4,5,4);
		_delay_ms(bremse);
		led(4,2,5);
		_delay_ms(bremse);
		led(4,1,2);
		_delay_ms(bremse);
		led(3,4,1);
		_delay_ms(bremse);
		led(3,5,4);
		_delay_ms(bremse);
		led(3,2,5);
		_delay_ms(bremse);
		led(3,1,2);
		_delay_ms(bremse);
		
		led(3,2,1);
		_delay_ms(bremse);
		led(3,5,2);
		_delay_ms(bremse);
		led(3,4,5);
		_delay_ms(bremse);
		led(3,1,4);
		_delay_ms(bremse);
		led(4,3,1);
		_delay_ms(bremse);
		led(4,5,3);
		_delay_ms(bremse);
		led(4,3,5);
		_delay_ms(bremse);
		led(4,1,3);
		_delay_ms(bremse);
		
		led(3,2,1);
		_delay_ms(bremse);
		led(3,5,2);
		_delay_ms(bremse);
		led(3,4,5);
		_delay_ms(bremse);
		led(3,1,4);
		_delay_ms(bremse);
		led(3,3,1);
		_delay_ms(bremse);
		led(3,5,3);
		_delay_ms(bremse);
		led(3,3,5);
		_delay_ms(bremse);
		led(3,1,3);
		_delay_ms(bremse);
		led(2,3,1);
		_delay_ms(bremse);
		led(2,5,3);
		_delay_ms(bremse);
		led(2,3,5);
		_delay_ms(bremse);
		led(2,1,3);
		_delay_ms(bremse);
		}
		
		while(up <= 34)// Die 9 mittleren innersten Ebene 5 + jedes 2 von aussen fourth drop
		{
		led(1,3,3);
		_delay_ms(bremsel);
		led(2,3,3);
		_delay_ms(bremsel);
		led(3,3,3);
		_delay_ms(bremsel);
		led(4,3,3);
		_delay_ms(bremsel);
		led(5,3,3);
		_delay_ms(bremsel);
		
		led(5,3,3);
		_delay_ms(bremse);
		led(5,2,2);
		_delay_ms(bremse);
		led(5,2,3);
		_delay_ms(bremse);
		led(5,2,4);
		_delay_ms(bremse);
		led(5,3,4);
		_delay_ms(bremse);
		led(5,4,4);
		_delay_ms(bremse);
		led(5,4,3);
		_delay_ms(bremse);
		led(5,4,2);
		_delay_ms(bremse);
		led(5,3,2);
		_delay_ms(bremse);
			
		led(5,2,5);
		_delay_ms(bremse);
		led(5,4,5);
		_delay_ms(bremse);
		led(5,5,4);
		_delay_ms(bremse);
		led(5,5,2);
		_delay_ms(bremse);
		led(5,4,1);
		_delay_ms(bremse);
		led(5,2,1);
		_delay_ms(bremse);
		led(5,1,2);
		_delay_ms(bremse);
		led(5,1,4);
		_delay_ms(bremse);
	
		led(4,2,1);
		_delay_ms(bremse);
		led(4,5,2);
		_delay_ms(bremse);
		led(4,4,5);
		_delay_ms(bremse);
		led(4,1,4);
		_delay_ms(bremse);
		led(5,3,1);
		_delay_ms(bremse);
		led(5,5,3);
		_delay_ms(bremse);
		led(5,3,5);
		_delay_ms(bremse);
		led(5,1,3);
		_delay_ms(bremse);
		
		led(5,4,1);
		_delay_ms(bremse);
		led(5,5,4);
		_delay_ms(bremse);
		led(5,2,5);
		_delay_ms(bremse);
		led(5,1,2);
		_delay_ms(bremse);
		led(4,4,1);
		_delay_ms(bremse);
		led(4,5,4);
		_delay_ms(bremse);
		led(4,2,5);
		_delay_ms(bremse);
		led(4,1,2);
		_delay_ms(bremse);
		led(3,4,1);
		_delay_ms(bremse);
		led(3,5,4);
		_delay_ms(bremse);
		led(3,2,5);
		_delay_ms(bremse);
		led(3,1,2);
		_delay_ms(bremse);
		led(2,4,1);
		_delay_ms(bremse);
		led(2,5,4);
		_delay_ms(bremse);
		led(2,2,5);
		_delay_ms(bremse);
		led(2,1,2);
		_delay_ms(bremse);
		
		led(1,3,3);
		_delay_ms(bremsel);
		led(2,3,3);
		_delay_ms(bremsel);
		led(3,3,3);
		_delay_ms(bremsel);
		led(4,3,3);
		_delay_ms(bremsel);
		led(5,3,3);
		_delay_ms(bremsel);
		
		led(3,2,1);
		_delay_ms(bremse);
		led(3,5,2);
		_delay_ms(bremse);
		led(3,4,5);
		_delay_ms(bremse);
		led(3,1,4);
		_delay_ms(bremse);
		led(4,3,1);
		_delay_ms(bremse);
		led(4,5,3);
		_delay_ms(bremse);
		led(4,3,5);
		_delay_ms(bremse);
		led(4,1,3);
		_delay_ms(bremse);
		
		led(3,2,1);
		_delay_ms(bremse);
		led(3,5,2);
		_delay_ms(bremse);
		led(3,4,5);
		_delay_ms(bremse);
		led(3,1,4);
		_delay_ms(bremse);
		led(3,3,1);
		_delay_ms(bremse);
		led(3,5,3);
		_delay_ms(bremse);
		led(3,3,5);
		_delay_ms(bremse);
		led(3,1,3);
		_delay_ms(bremse);
		led(2,3,1);
		_delay_ms(bremse);
		led(2,5,3);
		_delay_ms(bremse);
		led(2,3,5);
		_delay_ms(bremse);
		led(2,1,3);
		_delay_ms(bremse);
		
		led(2,2,1);
		_delay_ms(bremse);
		led(2,5,2);
		_delay_ms(bremse);
		led(2,4,5);
		_delay_ms(bremse);
		led(2,1,4);
		_delay_ms(bremse);
		led(1,3,1);
		_delay_ms(bremse);
		led(1,5,3);
		_delay_ms(bremse);
		led(1,3,5);
		_delay_ms(bremse);
		led(1,1,3);
		_delay_ms(bremse);
		}*/
	
	ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS0) | (1<<ADPS1);
	ADMUX |= ((1<<MUX0) | (1<<MUX1) | (1<<MUX2));
	ADMUX |= (1<<REFS1);
	ADCSRA |= (1<<ADSC);
	
	while(ADCSRA & (1<<ADSC));
	result = ADCW;
	
	
	
	while(1)
	{
	
		if(adc() > 511)
		{
			DDRA = 0xFF;
			DDRD = 0xFF;
			PORTA = 0b00011111;
			PORTD = 0b00000000;
		
		}
	//}//end of while
		
	//up = 0;	
	}
		
	//End of while
	return 0;
}

uint16_t adc(void)
{
			DDRA &= ~(1<<PA7);
			ADCSRA |= (1<<ADSC);
			while (ADCSRA & (1<<ADSC));
			result = ADCW;
			

	return result;
}

	