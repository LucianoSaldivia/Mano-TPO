/*******************************************************************************************************************************//**
 *
 * @file		MDE_Adquisidor.c
 * @brief		--Descripción del Módulo--
 * @date		22/10/2018
 * @author		Esteban Chiama
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/

#include "MDE_Adquisidor.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

// Constantes para el estado del ADQ
#define MEDIDOR_RESET		0
#define	MEDIDOR_INACTIVO	1
#define	MEDIDOR_ACTIVO		2

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

volatile uint8_t f_Start_Manotronic = 0;
volatile uint8_t f_StopSampling = 0;

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

static volatile uint32_t estado_medidor = MEDIDOR_RESET;

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/


void MDE_Adquisidor(volatile uint8_t *main_status) {

	uint8_t key = 0;

	// (protección)
	// caso: se está calibrando.
	if( (*main_status == BUSY) && (estado_medidor == MEDIDOR_INACTIVO) ){
		return;
	}

	// MdE: medición del ADC y transmisión de datos
	switch (estado_medidor) {
		case MEDIDOR_RESET:
			LCD_DisplayMsg("> ADQ. INACTIVO.", LCD_RENGLON_1, 0);
			LCD_DisplayMsg("> TPO Manotronic", LCD_RENGLON_2, 0);
			estado_medidor = MEDIDOR_INACTIVO;
			break;

		case MEDIDOR_INACTIVO:

			key = GetKey();

			// caso: comando para iniciar muestreo
			if ( ( command == START_ADC ) || ( key == SW2 ) ) {
				command = NO_COMMAND;
				estado_medidor = MEDIDOR_ACTIVO;
				*main_status = BUSY;

				f_ADC_Samples_rdy = 0;
				ResetBuffers();
				f_Start_Manotronic = 1;

				LCD_DisplayMsg("> MUESTREANDO.  ", LCD_RENGLON_1, 0);
				LED_Set(LED_STICK, LED_STICK_ON);	// prendo el led del stick, como testigo
			}
			break;


		case MEDIDOR_ACTIVO:
			// caso: muestra lista, la envío por el puerto serie
			if (f_ADC_Samples_rdy) {
				f_ADC_Samples_rdy = 0;
				Preparar_y_Enviar();
			}

			key = GetKey();

			// caso: comando para detener muestreo
			if ( (command == STOP_ADC) || (key == SW2) ) {
				command = NO_COMMAND;
				estado_medidor = MEDIDOR_INACTIVO;
				*main_status = FREE;

				f_StopSampling = 1;
				LCD_DisplayMsg("> INACTIVO     ", LCD_RENGLON_1, 0);
				LED_Set(LED_STICK, LED_STICK_OFF);	// apago el led del stick
			}
			break;

		default:
			estado_medidor = MEDIDOR_INACTIVO;
			break;
	}
}
