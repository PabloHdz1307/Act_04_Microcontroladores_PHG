/*
 * Act_03.c
 *Ingeniería en Telecomunicaciones, Sistemas y Electrónica
 *Facultad de Estudios Superiores Cuautitlán
 *Actividad número 4.
 *Microcontroladores 1859
 * Author : Pablo Hernández Gómez
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "ext_int.h"
#include "comp.h"
#include "timer.h"
#include "lcd_i2c.h"

volatile unsigned long counter = 0;
volatile unsigned char flag_lcd_update = 0;
volatile unsigned char flag_temp = 0;
volatile unsigned char flag_int = 0;

int main(void)
{
	char texto[17];
	unsigned long show_counter;	
	
	init_int0();
	init_comp();
	lcd_i2c_init();
	init_timer1();
	sei();
	while (1)
	{
		//Lógica del comparador
		if (flag_lcd_update == 1)
		{
			flag_lcd_update = 0;
		
			if (flag_temp == 1)
			{
				lcd_i2c_col_row(1, 1);
				lcd_i2c_write_string("¡Temp. Alta!");
			}
		
		//Lógica de la interrupción externa
		else if (flag_int == 1)
		{
			lcd_i2c_col_row(1, 1);
			lcd_i2c_write_string("Atender      ");
			lcd_i2c_col_row(1,2);
			lcd_i2c_write_string("Interrupcion");
		}
		
		//Lógica del contador (programa principal)
			else
			{
				//se deshabilitan las interrupciones
				cli();
				//copia el valor del contador (timer.c)
				show_counter = counter;
				sei();
			
				sprintf(texto, "Count: %-6lu", show_counter);
			
				//Escribir en el display
				lcd_i2c_col_row(1, 1);
				lcd_i2c_write_string(texto);
				lcd_i2c_col_row(1, 2);
				lcd_i2c_write_string("                ");
			}
		}
	}
}

