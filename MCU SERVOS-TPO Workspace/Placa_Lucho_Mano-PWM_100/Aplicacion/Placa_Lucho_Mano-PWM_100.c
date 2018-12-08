/*
===============================================================================
 Name        : Placa_Lucho_Mano-PWM_100.c
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
#include "PR_Teclas.h"

#include "MDE_PC_Mano.h"
#include "MDE_Guante_Mano.h"

int main(void) {
	volatile uint8_t main_status = FREE;

	Kit_Init();
	LED_Set(LED_STICK, LED_STICK_OFF);

    while(1) {

    	RX_Mensajes();
    	MDE_PC_Mano(&main_status);
    	MDE_Guante_Mano(&main_status);

    }

    return 0 ;
}
