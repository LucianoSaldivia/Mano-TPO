/*******************************************************************************************************************************//**
 *
 * @file		DR_Teclas.c
 * @brief		--Descripción del Módulo--
 * @date		Nov 22, 2018
 * @author		Esteban E. Chiama
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/


#include "DR_Teclas.h"


/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/


#define REBOTES		4


// Teclas (switches) de la placa de info II (4x1).
// SW5 es compartido con la entrada digital ED0.
#define		PORT_PIN_SW1			2,10
#define		PORT_PIN_SW2			0,18
#define		PORT_PIN_SW3			0,10
#define		PORT_PIN_SW4			2,13
#define		PORT_PIN_SW5			1,26


#define	ESPERANDO_TECLA			1
#define	VALIDAR_TECLA			2
#define	TECLA_PRESIONADA		3


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


volatile uint8_t Key_Pressed = NO_KEY;


/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/


uint8_t DriverTecladoHW(void);

void Teclado5x1_SW_Debounce(uint8_t CodigoActual);


 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/


/*
 * Función para la Lectura de las GPIO asignadas a las teclas
*/
uint8_t DriverTecladoHW(void){

		if( GetPIN(PORT_PIN_SW1 , BAJO ) ){
			return SW1;
		}

		if( GetPIN(PORT_PIN_SW2 , BAJO ) ){
			return SW2;
		}

		if( GetPIN(PORT_PIN_SW3 , ALTO ) ){
			return SW3;
		}

		if( GetPIN(PORT_PIN_SW4 , BAJO ) ){
			return SW4;
		}

//		if( GetPIN(PORT_PIN_SW5 , BAJO ) ){
//			return SW4;
//		}

		return NO_KEY;
}


/*
 * Función anti-rebote de las teclas pulsadas.
 * REBOTES: Cantidad de veces que se cuenta un cambio de estado hasta darlo por válido.
*/
void Teclado5x1_SW_Debounce(uint8_t CodigoActual){
	static uint8_t codigoAnterior = NO_KEY;
	static uint8_t estado = ESPERANDO_TECLA;
	static uint8_t contTeclaEstable = 0;

	switch (estado) {
		case ESPERANDO_TECLA:
			if (CodigoActual != NO_KEY) {
				codigoAnterior = CodigoActual;
				contTeclaEstable = 0;
				estado = VALIDAR_TECLA;
			}
			break;
		case VALIDAR_TECLA:
			if (CodigoActual != codigoAnterior) {
				estado = ESPERANDO_TECLA;
			} else {
				contTeclaEstable++;
				if (contTeclaEstable == REBOTES) {
					Key_Pressed = CodigoActual;
					estado = TECLA_PRESIONADA;
				}
			}
			break;
		case TECLA_PRESIONADA:
			if (CodigoActual != codigoAnterior) {
				estado = ESPERANDO_TECLA;
			}
			break;
		default:
			estado = ESPERANDO_TECLA;
			break;
	}
}

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/


/* 
 * Inicializacion del teclado de 4x1 de la placa BASE Infotronic
*/
void Switches_Initialize(void) {

	SetPINSEL(PORT_PIN_SW1, PINSEL_GPIO);
	SetPINSEL(PORT_PIN_SW2, PINSEL_GPIO);
	SetPINSEL(PORT_PIN_SW3, PINSEL_GPIO);
	SetPINSEL(PORT_PIN_SW4, PINSEL_GPIO);
//	SetPINSEL(PORT_PIN_SW5, PINSEL_GPIO);

	SetDIR(PORT_PIN_SW1, GPIO_ENTRADA);
	SetDIR(PORT_PIN_SW2, GPIO_ENTRADA);
	SetDIR(PORT_PIN_SW3, GPIO_ENTRADA);
	SetDIR(PORT_PIN_SW4, GPIO_ENTRADA);
//	SetDIR(PORT_PIN_SW5, GPIO_ENTRADA);

	SetResistorMode(PORT_PIN_SW1, PINMODE_PULLUP);
	SetResistorMode(PORT_PIN_SW2, PINMODE_PULLUP);
	SetResistorMode(PORT_PIN_SW3, PINMODE_PULLUP);
	SetResistorMode(PORT_PIN_SW4, PINMODE_PULLUP);
//	SetResistorMode(PORT_PIN_SW5, PINMODE_PULLUP);

}


void DriverSwitches(void){

	uint8_t CodigoActual;

	CodigoActual = DriverTecladoHW();

	Teclado5x1_SW_Debounce(CodigoActual);

}
