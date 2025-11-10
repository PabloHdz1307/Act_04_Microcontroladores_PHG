/*
 * comp.c
 *
 * Created: 10/22/2025 4:28:49 PM
 *  Author: Pablo Hernandez
 */ 

#include <avr/interrupt.h>
#include <avr/io.h>
#include "i2c.h"
#include "lcd_i2c.h"
#include "variables.h"

ISR(ANALOG_COMP_vect)
{
	if ( ACSR & (1 << ACO) )
	{
		//SI ACO = 1 activa la bandera de alerta de alta temperatura
		flag_temp = 1;
		//Reconfigurar la interrupción por flanco de bajada
		ACSR &= ~(1 << ACIS0);
	}
	else
	{
		//Si ACO = 0 desactiva la bandera de alerta
		flag_temp = 0;
		//Reconfigura la interrupción por flanco de subida
		ACSR |= (1 << ACIS0);
	}
}


void init_comp(void)
{
	ACSR |= (1 << ACIS0 | 1 << ACIS1); //interrupt when Input > Vref
	ACSR |= (1 << ACIE); //enable interrupt
}