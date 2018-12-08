/*******************************************************************************************************************************//**
 *
 * @file		AP_UART_0.c
 * @brief		--Descripción del Módulo--
 * @date		Nov 12, 2018
 * @author		Esteban Chiama
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "AP_UART_0.h"
/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

// Para MDE de recepción de mensajes
#define ESPERANDO			0
#define RECIBIENDO_TRAMA	1
#define	RECIBIENDO_DATOS	2

// protección overflow
#define MAX_TRAMA_RX_COMANDOS		8
#define	MAX_TRAMA_RX_DATOS			14

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

volatile uint8_t command = NO_COMMAND;

volatile uint8_t f_UART_Data = NO_DATA;
volatile Lecturas_Mano_1000 UART_Data_Adaptada;

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

void leer_comandos( const char msg_rx[] );
void leer_datos( const uint8_t trama_datos[] );

Lecturas_Mano_1000 Adaptar_Manos( Mano_t ManoUART);

/***********************************************************************************************************************************
*** FUNCIONES PRIVADAS AL MODULO
**********************************************************************************************************************************/

void leer_comandos( const char trama[] ){

	// Comando para el muestreo
	// Formato: MX
	// Donde X puede ser: '0' detener, '1' iniciar
	if ((trama[0]) == 'M') {
		if ( trama[1] == 'P' ){
			if( trama[2] == 'M' ){
				if( trama[3] == '1' ){
					command = MODO_PC_MANO_START;
				}
				else if( trama[3] == '0' ){
					command = MODO_PC_MANO_STOP;
				}
			}
		}
	}

}

void leer_datos( const uint8_t trama_datos[] ){
	Mano_t UART_Data;

	// Formato de los datos recibidos:		Menique , Anular, Medio, Indice, Pulgar
	// Cada dedo son 2 bytes
	// El primero siendo el más significativo

	if( (trama_datos[2] == ',') && (trama_datos[5] == ',') && (trama_datos[8] == ',') && (trama_datos[11] == ',') ){

		// recomponer uint16_t

		UART_Data.Menique = ( trama_datos[0] << 8 );	// most significant byte
		UART_Data.Menique |= trama_datos[1];			// less significant byte

		UART_Data.Anular = ( trama_datos[3] << 8 );
		UART_Data.Anular |= trama_datos[4];

		UART_Data.Medio = ( trama_datos[6] << 8 );
		UART_Data.Medio |= trama_datos[7];

		UART_Data.Indice = ( trama_datos[9] << 8 );
		UART_Data.Indice |= trama_datos[10];

		UART_Data.Pulgar = ( trama_datos[12] << 8 );
		UART_Data.Pulgar |= trama_datos[13];


		UART_Data_Adaptada = Adaptar_Manos(UART_Data);
		f_UART_Data = 1;
	}
}

Lecturas_Mano_1000 Adaptar_Manos( Mano_t ManoUART){
	Lecturas_Mano_1000 Adaptada;

	Adaptada.Pulgar = ManoUART.Pulgar;
	Adaptada.Indice = ManoUART.Indice;
	Adaptada.Mayor = ManoUART.Medio;
	Adaptada.Anular = ManoUART.Anular;
	Adaptada.Menor = ManoUART.Menique;

	return Adaptada;
}

/**********************************************************************************************************************************
*** FUNCIONES GLOBALES AL MODULO
**********************************************************************************************************************************/

void RX_Mensajes(void) {
	static uint8_t estado_rx = ESPERANDO;
	static char msg_rx[MAX_TRAMA_RX_COMANDOS] = {0};
	static uint8_t datos_rx[MAX_TRAMA_RX_DATOS] = {0};
	static uint8_t inx_msg_rx = 0;
	uint8_t data;

	// Chequeo si llegó un msje...
	if ( U0_PopRx( &data ) ) {

		// MdE: Análisis de la trama recibida
		switch ( estado_rx ) {

			case ESPERANDO:

				// Espero el caracter de inicio de la trama ('$') (para comandos)
				if ( (char)data == '$' ) {
					inx_msg_rx = 0;
					estado_rx = RECIBIENDO_TRAMA;
				}

				// caso: se reciben datos
				else if ( (char)data == '#' ) {
					inx_msg_rx = 0;
					estado_rx = RECIBIENDO_DATOS;
				}

				break;

			case RECIBIENDO_TRAMA:
				// caso: se terminó de recibir la trama ('#')
				if ( (char)data == '#' ) {
					leer_comandos(msg_rx);
					estado_rx = ESPERANDO;
				}
				// caso: no se llegó al fin de trama ('#')
				if ( (char)data != '#' ) {
					// protección overflow
					if (inx_msg_rx > MAX_TRAMA_RX_COMANDOS-1) {
						estado_rx = ESPERANDO;
						break;
					}
					// recibo y almaceno
					msg_rx[inx_msg_rx] = (char)data;
					inx_msg_rx++;
				}
				break;

			case RECIBIENDO_DATOS:
				// caso: se terminó de recibir el dato ('$')
				if ( (char)data == '$' ) {
					leer_datos(datos_rx);
					estado_rx = ESPERANDO;
				}
				// caso: no se llegó al fin de trama ('#')
				if ( (char)data != '$' ) {
					// protección overflow
					if (inx_msg_rx > MAX_TRAMA_RX_DATOS-1) {
						estado_rx = ESPERANDO;
						break;
					}
					// recibo y almaceno.
					datos_rx[inx_msg_rx] = data;
					inx_msg_rx++;
				}
				break;

			default:
				estado_rx = ESPERANDO;
				break;
		}
	}
}
