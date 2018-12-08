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

int main ( void ) {

	Kit_Init();

	Start_Sampling();

	while(1){
//		RX_Mensajes();
//		MDE_Adquisidor();
	}

	return 0;
}
