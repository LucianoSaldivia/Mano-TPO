/*
 * dr_timer_adc.h
 *
 *  Created on: Oct 14, 2018
 *      Author: cha
 */

#ifndef REGS_LPC176X
#define REGS_LPC176X

#include "Regs_LPC176x.h"

#endif /* REGS_LPC176X */

#ifndef INC_DR_TIMER_ADC_H_
#define INC_DR_TIMER_ADC_H_


#include "FW_PINSEL.h"

// Constantes
#define FRECUENCIA_MUESTREO	(double)4000
#define MICROSEG			(double)1/(double)1000000

// Variables globales para incluír en otros .c
extern volatile uint16_t ADC_sample;
extern volatile uint8_t ADC_dato_disponible;


/***************************/
/* Prototipos de Funciones */
/***************************/

// Funciones para el Timer
void Timer0_ADC_Init( void );
void TIMER0_IRQHandler( void );

// Funciones para el ADC
void ADC_Init( void );
void ADC_InputSelect( uint8_t selectedInput );
void ADC_Start( void );
void ADC_IRQHandler( void );

void Start_Sampling( void );
void Stop_Sampling( void );

#endif /* INC_DR_TIMER_ADC_H_ */
