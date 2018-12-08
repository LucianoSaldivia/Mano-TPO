/*******************************************************************************************************************************//**
 *
 * @file		DR_ADC_5canales_Timer.h
 * @brief		--Descripción del Módulo--
 * @date		14/10/2018
 * @author		Esteban Chiama
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef INC_DR_ADC_5CANALES_TIMER_H_
#define INC_DR_ADC_5CANALES_TIMER_H_

/***********************************************************************************************************************************
 *** INCLUDES PÚBLICOS
 **********************************************************************************************************************************/


#include "Regs_LPC176x.h"
#include "DR_PINSEL.h"
#include "DR_GPIO.h"


/***********************************************************************************************************************************
 *** DEFINES PÚBLICOS
 **********************************************************************************************************************************/

#define FS_CALIBRACION		200
#define	FS_MANOTRONIC		2500

/***********************************************************************************************************************************
 *** MACROS PÚBLICAS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PÚBLICOS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PÚBLICAS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PÚBLICAS (PARA INCLUIR EN OTRO .C)
 **********************************************************************************************************************************/


extern volatile uint16_t ADC_sample;
extern volatile uint8_t ADC_dato_disponible;


/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES PÚBLICAS
 **********************************************************************************************************************************/


void TIMER0_ADC_FS_Config(uint16_t input_fs);
void TIMER0_ADC_Init( void );

void ADC_Init( void );

void Start_Sampling( void );
void Stop_Sampling( void );


#endif /* INC_DR_ADC_5CANALES_TIMER_H_ */
