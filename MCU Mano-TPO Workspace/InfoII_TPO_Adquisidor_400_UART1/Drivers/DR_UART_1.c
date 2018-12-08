/*******************************************************************************************************************************//**
 *
 * @file		DR_UART_1.c
 * @brief		--Descripción del Módulo--
 * @date		Nov 12, 2018
 * @author		Esteban Chiama
 *
 **********************************************************************************************************************************/


/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/


#include "DR_UART_1.h"


/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/


// Registros (defines para portabilidad)
#define REGISTRO_RX		U1RBR
#define REGISTRO_TX		U1THR
#define REGISTRO_LSR		U1LSR


// Casos de IIR (interrupt identification)
#define MODEM		0
#define	TX		1
#define	RX		2
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


volatile uint8_t f_U1_Tx = 0;  // Flag de Tx en curso


/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/


void UART1_IRQHandler ( void ) {

	uint8_t iir, interrupt_ID;
	uint8_t AnalisisError;
	uint8_t checker;
	uint8_t dato;	// To read RX register
	uint32_t lsr;

	do {

		iir = U1IIR;  // Flags de interrupción clear on read.

		interrupt_ID = ( iir >> 1 ) & 0x3;

		// caso: Data Ready (Interrupción por RX)
		if ( interrupt_ID == RX ) {

			BORRAR_FLAG_RX;
			dato = REGISTRO_RX;
			U1_PushRx( (uint8_t) dato );

		}

		// caso: THRE (Interrupción por TX)
		if ( interrupt_ID == TX ) {

			BORRAR_FLAG_TX;
			checker = U1_PopTx(&dato);

			// caso: hay un dato en el bufferTx para enviar
			if ( checker ) {
				REGISTRO_TX = (uint8_t) dato;
			}

			//caso: no hay más datos a enviar
			if( checker == 0 ) {
				f_U1_Tx = 0;
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

				default:
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


void UART1_Initialize ( void ) {

	// 1. Alimentar el periférico.
	PCONP |= ( (0x1)<<4 );	// Bit 4 es la UART1

	// 2. Clock del periférico.
	PCLKSEL0 &= ~( (0x3) << 8 );  // Bits 8:9 == 0 => CCLK/4 = 25MHz.

	// 3. Configuración de trama. Largo de trama, paridad, bit de stop, etc.

	U1LCR |= ( (0x3)<<0 );		// Bit 0:1. Largo de trama. 11 es 8 bits
	U1LCR &= ~( (0x1)<<2 );		// Bit 2. Stop bits. 0 es 1 bit
	U1LCR &= ~( (0x1)<<3 );		// Bit 3. Parity enable. 0 es desactivada
	U1LCR &= ~( (0x1)<<6 );		// Bit 6. Break Control. 0 es disabled

	// 4. Configuración del BaudRate. (hecho para 115200 baudios)

	/* Ecuación:
	 *
	 * 									PCLK [Hz]
	 * Baudrate =	----------------------------------------------------
	 *				16 x (256 x DLM + DLL ) x ( 1 + DIVADDVAL / MULVAL )
	 */

	U1LCR |= ( (0x1) << 7 );	// DLAB == 1 para acceder a registros DLM y DLL
	
	U1DLM &= ~(0xFF) ;		// DLM == 0

	U1DLL &= ~(0xFF);		// DLL clear	
	U1DLL |= ( (0xC) << 0 );	// DLL == 12

	*U1FDR = 0;
	*U1FDR |= ( (0xF)<<4 );    	// Bits 4:7 . MULVAL == 15
	*U1FDR |= 0x2;	 		// Bits 0:3 . DIVADDVAL == 2

	// deshabilitamos FIFO (por las dudas)
	U1FCR &= ~ ( (0x1) << 0 ) ;

	// 5. Configuración de pines para función de TX y RX
	SetPINSEL(P0, 15, PINSEL_FUNC1);		//TX1D : PIN ??	-> 	P0[15]
	SetPINSEL(P0, 16, PINSEL_FUNC1);		//RX1D : PIN ??	-> 	P0[16]
	SetResistorMode(P0, 16, PINMODE_TRISTATE);	// rx pin mode : ninguno

	// 6. Interrupciones del periférico

	U1LCR &= ~( (0x1) << 7 );		// DLAB == 0 para acceder a registros IER
	U1IER |= ( (0x1) << 0 );		// Habilito int. por rx	
	U1IER |= ( (0x1) << 1 );		// Habilito int. por tx
	
	// 7. Interrupción del micro
	ISER0 |= ( (0x1) << 6 );			// Habilito int. de la UART1 en el NVIC
}


// U1_StartTx es una función para hacer la transmisión del primer dato, que debe ser manual
void U1_StartTx(uint8_t dato) {

	REGISTRO_TX = dato;
	f_U1_Tx = 1;

	return;
}
