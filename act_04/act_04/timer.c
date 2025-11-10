/*
 * timer.c
 *
 * Created: 11/9/2025 10:14:22 PM
 *  Author: Pablo Hernandez
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "variables.h"

//se define el tiempo en que aumentará el valor del contador (250ms)
#define counter_speed 250
#define pause_time 5000

void init_timer1(void)
{
	//Set Clear Timer on Compare Match (CTC)
	TCCR1B |= (1 << WGM12);
	//Set prescaler 64
	TCCR1B |= (1 << CS11) | (1 << CS10);
	//Para un periodo de 1ms
	//OCR1A = ((Fosc) / (prescaler * freq)) - 1
	//OCR1A = ((16 Mhz) / (64 * 1 kHz)) -1 = 249
	OCR1A = 249;
	//Timer 1, Output Compare A Match Interrupt Enable
	TIMSK1 |= (1 << OCIE1A);
	//Set timer to 0
	TCNT1 = 0;
	
}

ISR(TIMER1_COMPA_vect)
{
	static unsigned int contador_ms = 0;
	static unsigned int time_delay = 0;
	//se aumentará el valor del contador cada milisegundo.
	contador_ms++;
	
	if (flag_int == 1)
	{
		//Comienza a contar para un delay de 5 segundos
		time_delay++;
		
		if (time_delay >= pause_time)
		{
			//reinicia el contador del delay 
			time_delay = 0;
			//Baja la bandera
			flag_int = 0;
			
			//Habilitamos la interrupción nuevamente
			EIMSK |= (1 << INT0);
		}
	}
	else
	{
		//Si la int no se activó, mantiene en 0 el contador de delay.
		time_delay = 0;
	}
	
	
	if (contador_ms >= counter_speed)
	{
		//si pasó el tiempo de espera. Reiniciamos el contador
		contador_ms = 0;
		
		if (flag_temp == 0 && flag_int == 0)
		{
			//incrementamos el contador principal si las banderas de 
			//temperatura e interrupción están inactivas
			counter++;
			if (counter > 100000)
			{
				counter = 0;
			}
		}
		flag_lcd_update = 1;
	}
	
}
