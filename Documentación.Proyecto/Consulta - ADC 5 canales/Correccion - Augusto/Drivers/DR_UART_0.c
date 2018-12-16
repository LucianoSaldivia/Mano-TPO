/*******************************************************************************************************************************//**
 *
 * @file		DR_UART_0.c
 * @brief		--Descripción del Módulo--
 * @date		Nov 12, 2018
 * @author		Esteban Chiama
 *
 **********************************************************************************************************************************/


/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/


#include "DR_UART_0.h"


/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/


// Registros (defines para portabilidad)
#define REGISTRO_RX		U0RBR
#define REGISTRO_TX		U0THR
#define REGISTRO_LSR	U0LSR


// Casos de IIR (interrupt identification)
#define MODEM		0
#define	TX			1
#define	RX			2
#define ERRORES		3


// Errores
#define OE	1
#define PE	2
#define FE	4
#define BI	8


/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/


// En caso de micro sin reset de flags de interrupción por hardware, se deben usar estas MACROS para despejarlas.
// Si el micro es con reset por hardware, estas macro deben ser vacías.
#define BORRAR_FLAG_RX
#define BORRAR_FLAG_TX


/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/


volatile uint8_t f_U0_Tx = 0;  // Flag de Tx en curso


/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/


void UART0_IRQHandler ( void ) {

	uint8_t iir, interrupt_ID;
	uint8_t AnalisisError;
	uint8_t checker;
	uint8_t dato;	// To read RX register
	uint32_t lsr;

	do {

		iir = U0IIR;  // Flags de interrupción clear on read.

		interrupt_ID = ( iir >> 1 ) & 0x3;

		// caso: Data Ready (Interrupción por RX)
		if ( interrupt_ID == RX ) {

			BORRAR_FLAG_RX;
			dato = REGISTRO_RX;
			U0_PushRx( (uint8_t) dato );

		}

		// caso: THRE (Interrupción por TX)
		if ( interrupt_ID == TX ) {

			BORRAR_FLAG_TX;
			checker = U0_PopTx(&dato);

			// caso: hay un dato en el bufferTx para enviar
			if ( checker ) {
				REGISTRO_TX = (uint8_t) dato;
			}

			//caso: no hay más datos a enviar
			if( checker == 0 ) {
				f_U0_Tx = 0;
			}

		}

		// Caso: interrupción por algún error
		if ( interrupt_ID == ERRORES ){

			lsr = REGISTRO_LSR;
			AnalisisError = ( lsr >> 1 ) & 0x0F;

			switch ( AnalisisError ){

				case OE:
					// AVISAR POR OE
					break;

				case PE:
					// AVISAR POR PE
					break;

				case FE:
					// AVISAR POR FE
					break;

				case BI:
					// AVISAR POR BI
					break;

			}

		}


	} while(!(iir & 0x01));	/* me fijo si cuando entré a la ISR había otra
						    int. pendiente de atención: b0=1 (ocurre únicamente
						    si dentro del mismo espacio temporal llegan dos
						    interrupciones a la vez) */
}


 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/


void UART0_Initialize ( void ) {

	// 1. Alimentar el periférico.
	PCONP |= ( (0x01)<<3 );

	// 2. Clock del periférico.
	PCLKSEL0 &= ~(0x03 << 6);  // Bits 6:7 == 0 => CCLK/4 = 25MHz.

	// 3. Configuración de trama. Largo de trama, paridad, bit de stop, etc.

	U0LCR |= ( (0x3)<<0 );		// Bit 0:1. Largo de trama. 11 es 8 bits
	U0LCR &= ~( (0x1)<<2 );		// Bit 2. Stop bits. 0 es 1 bit
	U0LCR &= ~( (0x1)<<3 );		// Bit 3. Parity enable. 0 es desactivada
	U0LCR &= ~( (0x1)<<6 );		// Bit 6. Break Control. 0 es disabled

	// 4. Configuración del BaudRate. (hecho para 115200 baudios)

	/* Ecuación:
	 *
	 * 									PCLK [Hz]
	 * Baudrate =	----------------------------------------------------
	 *				16 x (256 x DLM + DLL ) x ( 1 + DIVADDVAL / MULVAL )
	 */

	U0LCR |= ( (0x1)<<7 );		// DLAB == 1 para acceder a registros DLM y DLL
	U0DLM = 0;					// DLM == 0
	U0DLL = 0xC;				// DLL == 12

	*U0FDR = 0;
	*U0FDR |= ( (0xF)<<4 );    // Bits 4:7 . MULVAL == 15
	*U0FDR |= 0x02;	 		   // Bits 0:3 . DIVADDVAL == 2

	// 5. Configuración de pines para función de TX y RX
	SetPINSEL(P0, 2, PINSEL_FUNC1);		//TX1D : PIN ??	-> 	P0[2]
	SetPINSEL(P0, 3, PINSEL_FUNC1);		//RX1D : PIN ??	-> 	P0[3]

	// 6. Interrupciones

	U0LCR &= ~(0x01 << 7);		// DLAB == 0 para acceder a registros IER
	U0IER = 0x03;				// Habilito las interrupciones de RX y TX en la UART0
	ISER0 |= (1<<5);			// Habilito la interrupción de la UART0 en el NVIC

}


// U0_StartTx es una función para hacer la transmisión del primer dato, que debe ser manual
void U0_StartTx(uint8_t dato) {

	REGISTRO_TX = dato;
	f_U0_Tx = 1;

	return;
}
