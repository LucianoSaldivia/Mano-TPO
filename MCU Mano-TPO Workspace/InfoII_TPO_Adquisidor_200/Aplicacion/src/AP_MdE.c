/*
 * AP_uart.c
 *
 *  Created on: Oct 22, 2018
 *      Author: cha
 */

#include "AP_Controlador.h"
#include "AP_muestreo_mano.h"
#include "pr_muestreo_5canales.h"


// Estados
static uint32_t estado_medidor = MEDIDOR_RESET;
static uint8_t command = NO_COMMAND;


/*************/
/* FUNCIONES */
/*************/



void Controlador(void) {
	static char msg_LCD[2*LARGO_RENGLON];

	// MdE: medición del ADC y transmisión de datos
	switch (estado_medidor) {

		case MEDIDOR_RESET:
			LCD_DisplayMsg("> INACTIVO.     ", LCD_RENGLON_1, 0);
			LCD_DisplayMsg("> INFOII MANO TP", LCD_RENGLON_2, 0);
			estado_medidor = MEDIDOR_INACTIVO;
			break;

		case MEDIDOR_INACTIVO:
			// caso: comando para iniciar muestreo
			if ( command == START_ADC ) {
				command = NO_COMMAND;
				estado_medidor = MEDIDOR_ACTIVO;
				if( !is_ADC_ON() ){
					Sampling_Start();
					LCD_DisplayMsg("> MUESTREANDO.  ", LCD_RENGLON_1, 0);
					IO_LED_Set(IO_LED_STICK, ON);
				}
			}
			break;

		case MEDIDOR_ACTIVO:
			// caso: muestra lista, la envío por el puerto serie
			if (ADC_dato_disponible) {
				ADC_dato_disponible = 0;
				Preparar_y_Enviar();
			}

			// caso: comando para detener muestreo
			if ( command == STOP_ADC ) {
				command = NO_COMMAND;
				estado_medidor = MEDIDOR_INACTIVO;
				Sampling_Stop();
				LCD_DisplayMsg("> INACTIVO     ", LCD_RENGLON_1, 0);
				IO_LED_Set(IO_LED_STICK, OFF);
			}
			break;

		default:
			estado_medidor = MEDIDOR_INACTIVO;
			break;
	}
}

void RX_Mensajes(void) {
	uint8_t dato;
	static uint8_t index_msg_rx = 0;
	static char msg_rx[MAX_TRAMA_RX] = {0};
	static uint32_t estado_rx = ESPERANDO_TRAMA;

	// Chequeo si llegó un msje...
	if (!PopRx(&dato)) {

		// MdE: Análisis de la trama recibida
		switch (estado_rx) {

			case ESPERANDO_TRAMA:
				// Espero el caracter de inicio de la trama ('$')
				if ( (char)dato == '$' ) {
					index_msg_rx = 0;
					estado_rx = RECIBIENDO_TRAMA;
				}
				break;

			case RECIBIENDO_TRAMA:

				// caso: no se llegó al fin de trama ('#'), recibo y almaceno.
				if ( (char)dato != '#' ) {
					msg_rx[index_msg_rx] = (char)dato;
					index_msg_rx++;
					if (index_msg_rx > MAX_TRAMA_RX-1){
						estado_rx = ESPERANDO_TRAMA;
					}
					break;
				}

				// caso: se terminó de recibir la trama ('#')
				if ( (char)dato == '#' ){
					leer_comandos(msg_rx);
					estado_rx = ESPERANDO_TRAMA;
				}
				break;

				default:
				estado_rx = ESPERANDO_TRAMA;
				break;
		}
	}
}

void leer_comandos( const char trama[] ){
	uint8_t digitos=0;

	// Comando para el muestreo
	// Formato: MX
	// Donde X puede ser: '0' detener, '1' iniciar
	if ((trama[0]) == 'M') {

		if((trama[1]) == '0') {
			command = STOP_ADC;
		}

		else if ((trama[1]) == '1') {
			command = START_ADC;
		}
	}

}
