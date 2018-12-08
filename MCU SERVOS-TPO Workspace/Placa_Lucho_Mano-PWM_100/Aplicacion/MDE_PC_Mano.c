/*******************************************************************************************************************************//**
 *
 * @file		MDE_PC_Mano.c
 * @brief		--Descripción del Módulo--
 * @date		Dec 04, 2018
 * @author		Esteban Chiama
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "MDE_PC_Mano.h"
/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

// estado
#define	RESET		0
#define INACTIVE	1
#define	ACTIVE		2

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

static volatile uint8_t estado_PC_Mano = RESET;

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/

void MDE_PC_Mano(volatile uint8_t *main_status){
	uint8_t key;
	Lecturas_Mano_1000 ManoRecibida;

	// (protección)
	// caso: otra MDE en uso.
	if( (*main_status == BUSY) && (estado_PC_Mano == INACTIVE) ){
		return;
	}

	switch( estado_PC_Mano ){

	case RESET:
//		LCD_DisplayMsg("> MANO INACTIVA.", LCD_RENGLON_1, 0);
//		LCD_DisplayMsg("> TPO Manotronic", LCD_RENGLON_2, 0);
		estado_PC_Mano = INACTIVE;
		break;

	case INACTIVE:
		// caso: comando para comenzar el modo PC-Mano
		if( command == MODO_PC_MANO_START ){
			estado_PC_Mano = ACTIVE;
			*main_status = BUSY;
//			LCD_DisplayMsg( "M: PC > Mano    ", LCD_RENGLON_1, 0);
			// LED del stick como testigo
			LED_Set(LED_STICK, LED_STICK_ON);

			// Habilitamos PWM
			PWM_Enable_5_Channels();
		}
		break;

	case ACTIVE:
		// caso: dato recibido por UART
		if( f_UART_Data == DATA_AVAILABLE ){
			f_UART_Data = NO_DATA;
			ManoRecibida = UART_Data_Adaptada;
			PWM_Set_Lecturas( &ManoRecibida );
		}

		// caso: comando para detener el modo PC-Mano
		if( command == MODO_PC_MANO_STOP ){
			command = NO_COMMAND;
			estado_PC_Mano = INACTIVE;
			*main_status = FREE;
			// Para limpiar el buffer de teclado, y así ignorar teclas que hayan sucedido en el proceso
			key = GetKey();
//			LCD_DisplayMsg("> MANO INACTIVA.", LCD_RENGLON_1, 0);
			LED_Set(LED_STICK, LED_STICK_OFF);

			// deshabilitamos los PWM
			PWM_Disable_5_Channels();
		}
		break;

	default:
		estado_PC_Mano = INACTIVE;
		break;
	}

}
