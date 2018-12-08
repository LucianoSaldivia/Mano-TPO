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
#include "DR_Init.h"
#include "MDE_Adquisidor.h"
#include <AP_Guante_Muestreo.h>

int main ( void ) {

	volatile uint8_t manotronic_status = FREE;

	Kit_Init();

	while(1){
		RX_Mensajes();
		MDE_Adquisidor(&manotronic_status);
		MDE_Calibrar(&manotronic_status);
	}

	return 0;
}
