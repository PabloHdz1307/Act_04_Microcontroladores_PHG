/*
 * ext_int.c
 *
 *  Author: Pablo
 */
#include <avr/interrupt.h>
#include "variables.h"

ISR(INT0_vect)
{
	flag_int = 1;
	//Se deshabilita la interrupción para evitar el efecto de rebote
	EIMSK &= ~(1 << INT0);
}

void init_int0(void)
{
	//Configura PD2 como entrada
	DDRD &= ~(1 << PD2);
	//Activa resistencia de pull-up
	PORTD |= (1 << PD2);
	
	EICRA |= (1 << ISC00); //interruption on any logical change
	EIMSK |= (1 << INT0);
	
}