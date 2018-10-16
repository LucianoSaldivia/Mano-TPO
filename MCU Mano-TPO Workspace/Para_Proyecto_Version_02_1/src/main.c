/*
===============================================================================
 Name        : pruebaBiblioteca.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include <bibliotecaInfoII.h>

// TODO: insert other include files here
#include "AP_Prueba1.h"
#include "AP_PruebaUART.h"
// TODO: insert other definitions and declarations here


void timer1Handler(void){
	static volatile unsigned char EstadoRelay = 0;
	if( EstadoRelay ){
		EstadoRelay = 0;
		Relays(RELAY0, ON);
		Relays(RELAY1, ON);
		Relays(RELAY2, OFF);
		Relays(RELAY3, OFF);
	}else{
		EstadoRelay = 1;
		Relays(RELAY0, OFF);
		Relays(RELAY1, OFF);
		Relays(RELAY2, ON);
		Relays(RELAY3, ON);
	}

	TimerStart( 1, 20, timer1Handler, DEC );
}

int main ( void )
{
	Inicializacion();

	LCD_Display( "Esperando una ", DSP0, 0 );
	LCD_Display( "tecla nueva ...", DSP1, 0 );
	TimerStart( 1, 20, timer1Handler, DEC );

	while(1)
	{
		TimerEvent();
		MaquinaEstadosPrueba();
		MDE_UART();
	}
}
