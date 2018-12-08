/*******************************************************************************************************************************//**
 *
 * @file		DR_SysTick.c
 * @brief		--Descripción del Módulo--
 * @date		Nov 3, 2018
 * @author		Esteban Chiama
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/


#include "DR_SysTick.h"


/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/


#define MILISECOND	( (float) 1 / 1000 )
#define	MICROSECOND	( (float) 1 / 1000000 )
#define NANOSECOND	( (float) 1 / 1000000000 )

#define MAX_VALOR_RELOAD		16777215		// 2^24 - 1, porque RELOAD son 24 bits
#define TICKS_DEFAULT_2500MICRO		249999


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


uint32_t Ticks_Config( uint32_t time_units , uint8_t time_base );


 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/


void SysTick_Handler(void) {

	// Acá ponés lo que necesite tu programa.

	LCD_Driver();
	// Para el LCD
	if (LCD_delay){	// Esto es solamente para la inicialización del LCD
		LCD_delay--;
	}

	// Para comenzar el muestreo sin pinchar capas desde la aplicación
	if ( f_StartSampling == 1 ){
		f_StartSampling = 0;
		Start_Sampling();
	}

	// Para detener el muestreo sin pinchar capas desde la aplicación
	if ( f_StopSampling == 1 ){
		f_StopSampling = 0;
		Stop_Sampling();
	}

	DriverSwitches();

}

uint32_t Ticks_Config( uint32_t time_units , uint8_t time_base ){
	
	uint32_t CantidadTicks;	// N

	switch( time_base ){

		case MILI:
			CantidadTicks =  (uint32_t) ( ( time_units * MILISECOND / ( 10 * NANOSECOND ) ) - 1 );
			break;

		case MICRO:
			CantidadTicks = ( time_units *  MICROSECOND / ( 10 * NANOSECOND ) ) - 1;
			break;

		case NANO:
			CantidadTicks = ( time_units *  NANOSECOND / ( 10 * NANOSECOND ) ) - 1;
			break;

		default:
			CantidadTicks = TICKS_DEFAULT_2500MICRO;
			break;
	}

	return CantidadTicks;
}


 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/


/* 	T:		Tiempo entre interrupciones del SysTick
 * 	ticks:	1 ciclo del micro. Tiempo que tarda en hacer RELOAD--
 * 	N:		Cantidad de ticks para alcanzar ( T - 1 tick )
 *
 * 		T = (N+1)*ticks
 *
 */

void SysTick_Init ( uint32_t time_units , uint8_t time_base ) {

	uint32_t CantidadTicks;	// N

	if ( time_units >=  MAX_VALOR_RELOAD ) {
		CantidadTicks = TICKS_DEFAULT_2500MICRO;
	}
	else{
		CantidadTicks = Ticks_Config(time_units, time_base);
	}

	STRELOAD &= ~( (0xFFFFFF) << 0 );
	STRELOAD |= CantidadTicks;

	STCURR &= ~( (0xFFFFFF) << 0 );		// Reinicio el Current Value, esto también limpia el flag del counter.

	STCTRL |= ( (0x1) << 1 );	// Interrupción habilitada
	STCTRL |= ( (0x1) << 2 );	// Clock Source: del Micro
	STCTRL |= ( (0x1) << 0 );	// Enable
}
