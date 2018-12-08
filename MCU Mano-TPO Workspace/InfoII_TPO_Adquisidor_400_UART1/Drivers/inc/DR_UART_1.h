/*******************************************************************************************************************************//**
 *
 * @file		DR_UART_1.h
 * @brief		--Descripción del Módulo--
 * @date		Nov 12, 2018
 * @author		Esteban Chiama
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef DR_UART_1_H_
#define DR_UART_1_H_


/***********************************************************************************************************************************
 *** INCLUDES PÚBLICOS
 **********************************************************************************************************************************/


#include "Regs_LPC176x.h"
#include "DR_PINSEL.h"

#include "PR_UART_1.h"


/***********************************************************************************************************************************
 *** DEFINES PÚBLICOS
 **********************************************************************************************************************************/

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


extern volatile uint8_t f_U1_Tx;


/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES PÚBLICAS
 **********************************************************************************************************************************/


void UART1_Initialize ( void );
void U1_StartTx( uint8_t data );


#endif /* DR_UART_1_H_ */