/*******************************************************************************************************************************//**
 *
 * @file		PR_UART_1.c
 * @brief		--Descripción del Módulo--
 * @date		Nov 12, 2018
 * @author		Esteban Chiama
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/


#include "PR_UART_1.h"


/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/


// Largo de los buffers
#define TX_BUFFER_SIZE	32
#define RX_BUFFER_SIZE	32


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


// Buffers de Transmisión y Recepción
static volatile uint8_t bufferRx[RX_BUFFER_SIZE];
static volatile uint8_t bufferTx[TX_BUFFER_SIZE];


// Índices de los buffers de Recepción
static volatile uint8_t inx_Rx_in = 0;
static volatile uint8_t inx_Rx_out = 0;


// Índices de los buffers de Transmisión
static volatile uint8_t inx_Tx_in = 0;
static volatile uint8_t  inx_Tx_out = 0;


/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/

/*******************************************************/
/* Funciones que trabajan sobre el buffer de recepción */
/*******************************************************/


uint8_t U1_PushRx ( uint8_t data ) {

	bufferRx[ inx_Rx_in ] = data;
	inx_Rx_in++;
	inx_Rx_in %= RX_BUFFER_SIZE;

	return 1;
}


uint8_t U1_PopRx ( uint8_t *container ){

	if( inx_Rx_in == inx_Rx_out ){
		return 0;
	}

	*container = bufferRx[ inx_Rx_out ];
	inx_Rx_out ++;
	inx_Rx_out %= RX_BUFFER_SIZE;

	return 1;
}


/*********************************************************/
/* Funciones que trabajan sobre el buffer de transmisión */
/*********************************************************/


// La UART interrumpe por dato enviado y envía el próximo desde la misma interrupción.
// Entonces el primer dato se debe enviar manualmente.


uint8_t U1_PushTx ( uint8_t data ) {

	// caso: No se está transmitiendo, entonces se dá comienzo transmisión
	if ( f_U1_Tx == 0 ){
		U1_StartTx( data );
		return 1;
	}

	bufferTx[ inx_Tx_in ] = data;
	inx_Tx_in++;
	inx_Tx_in %= TX_BUFFER_SIZE;

	return 1;
}


// PopTx quita un dato del buffer de transmisión
// Si está vacío devuelve 0
uint8_t U1_PopTx ( uint8_t *container ) {

	if( inx_Tx_in == inx_Tx_out ){
		return 0;
	}

	// caso: PopTx
	*container = bufferTx[ inx_Tx_out ];
	inx_Tx_out++;
	inx_Tx_out %= TX_BUFFER_SIZE;

	return 1;
}


// Transmitir encola en el buffer de transmisión
// a lo sumo "size" bytes de "data_vector"
// Devuelve 0 si se llenó el buffer de transmisión (y deja de escribirlo)
// Devuelve 1 en caso de éxito
uint8_t Transmitir( void *data_vector, uint16_t size ) {

	uint16_t i;

	i=0;
	while( i < size  ){
		if ( ! U1_PushTx( ((uint8_t *)data_vector)[i] ) ){
			return 0;
		}
		i++;
	}

	return 1;
}
