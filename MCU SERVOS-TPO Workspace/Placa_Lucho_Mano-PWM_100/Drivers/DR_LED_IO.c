/*******************************************************************************************************************************//**
 *
 * @file		DR_LED_IO.c
 * @brief		--Descripción del Módulo--
 * @date		Nov 22, 2018
 * @author		Esteban E. Chiama
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/

#include "DR_LED_IO.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

// LED del stick
#define		PORT_PIN_LED_STICK		0,22

//Leds RGB:
#define		PORT_PIN_RGB_G			2,2
#define		PORT_PIN_RGB_R			2,3
#define		PORT_PIN_RGB_B			2,1

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/


void LED_Initialize(void){

	// LED del STICK
	SetPINSEL(PORT_PIN_LED_STICK, PINSEL_GPIO);
	SetDIR(PORT_PIN_LED_STICK, GPIO_SALIDA);
	SetPIN(PORT_PIN_LED_STICK, LED_STICK_OFF);

	//LEDs RGB
	SetPINSEL(PORT_PIN_RGB_R, PINSEL_GPIO);
	SetPINSEL(PORT_PIN_RGB_G, PINSEL_GPIO);
	SetPINSEL(PORT_PIN_RGB_B, PINSEL_GPIO);

	SetDIR(PORT_PIN_RGB_R, GPIO_SALIDA);
	SetDIR(PORT_PIN_RGB_G, GPIO_SALIDA);
	SetDIR(PORT_PIN_RGB_B, GPIO_SALIDA);

	SetPIN(PORT_PIN_RGB_R, OFF);
	SetPIN(PORT_PIN_RGB_G, OFF);	// no me anda el verde en mi placa
	SetPIN(PORT_PIN_RGB_B, OFF);
}


void LED_Set(uint8_t led, uint8_t estado){
	switch (led) {
		case LED_STICK:
			SetPIN(PORT_PIN_LED_STICK, estado);
			break;
		case RGB_R:
			SetPIN(PORT_PIN_RGB_R, estado);
			break;
		case RGB_G:
			SetPIN(PORT_PIN_RGB_G, estado);
			break;
		case RGB_B:
			SetPIN(PORT_PIN_RGB_B, estado);
			break;
		default:
			break;
	}
}

void LED_Toggle(uint8_t led){
	switch (led) {
		case LED_STICK:
			SetPIN(PORT_PIN_LED_STICK, !GetPIN(PORT_PIN_LED_STICK, ALTO));
			break;
		case RGB_R:
			SetPIN(PORT_PIN_RGB_R, !GetPIN(PORT_PIN_RGB_R, ALTO));
			break;
		case RGB_G:
			SetPIN(PORT_PIN_RGB_G, !GetPIN(PORT_PIN_RGB_G, ALTO));
			break;
		case RGB_B:
			SetPIN(PORT_PIN_RGB_B, !GetPIN(PORT_PIN_RGB_B, ALTO));
			break;
		default:
			break;
	}

}

uint8_t LED_GetStatus(uint8_t led){
	uint8_t estado = 0;

	switch (led) {
		case LED_STICK:
			estado = GetPIN(PORT_PIN_LED_STICK, ALTO);
			break;
		case RGB_R:
			estado = GetPIN(PORT_PIN_RGB_R, ALTO);
			break;
		case RGB_G:
			estado = GetPIN(PORT_PIN_RGB_G, ALTO);
			break;
		case RGB_B:
			estado = GetPIN(PORT_PIN_RGB_B, ALTO);
			break;
		default:
			break;
	}

	return estado;
}
