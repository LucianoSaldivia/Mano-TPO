/*******************************************************************************************************************************//**
 *
 * @file		DR_PWM.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		28 de oct. de 2018
 * @author		Saldivia, Luciano
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef DR_PWM_H_
#define DR_PWM_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/

#include "Regs_LPC176x.h"
#include "DR_Tipos.h"
#include "DR_PINSEL.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/

//!< ///////////////////   PWM1   //////////////////////////
//!< 0x40018000 : Registro del periférico PWM1:
#define		R_PWM1	( ( registro  * ) 0x40018000UL )

//!< Registros del periférico PWM1:
#define		PWM1IR		R_PWM1[0]		// 0x40018000
#define		PWM1TCR		R_PWM1[1]		// 0x40018004
#define		PWM1TC		R_PWM1[2]		// 0x40018008
#define		PWM1PR		R_PWM1[3]		// 0x4001800C

#define		PWM1PC		R_PWM1[4]		// 0x40018010
#define		PWM1MCR		R_PWM1[5]		// 0x40018014
#define		PWM1MR0		R_PWM1[6]		// 0x40018018
#define		PWM1MR1		R_PWM1[7]		// 0x4001801C
#define		PWM1MR2		R_PWM1[8]		// 0x40018020
#define		PWM1MR3		R_PWM1[9]		// 0x40018024
#define		PWM1CCR		R_PWM1[10]		// 0x40018028
#define		PWM1CR0		R_PWM1[11]		// 0x4001802C
#define		PWM1CR1		R_PWM1[12]		// 0x40018030
#define		PWM1CR2		R_PWM1[13]		// 0x40018034
#define		PWM1CR3		R_PWM1[14]		// 0x40018038
// R_PWM1[15] NO ESTA EN LA TABLA 445, 0x4001803C
#define		PWM1MR4		R_PWM1[16]		// 0x40018040
#define		PWM1MR5		R_PWM1[17]		// 0x40018044
#define		PWM1MR6		R_PWM1[18]		// 0x40018048
#define		PWM1PCR		R_PWM1[19]		// 0x4001804C
#define		PWM1LER		R_PWM1[20]		// 0x40018050
// R_PWM1[21] ~ R_PWM1[27] NO ESTA EN LA TABLA 445, 0x40018054 ~ 0x4001806C
#define		PWM1CTCR	R_PWM1[28]		// 0x40018070

//!< //////////BITS DE ANALISIS para las interrupciones PWM   ////////////////////
#define 	PWM_MR0_IIR_FLAG    0x01
#define 	PWM_MR1_IIR_FLAG    0x02
#define 	PWM_MR2_IIR_FLAG    0x04
#define 	PWM_MR3_IIR_FLAG    0x08
#define 	PWM_MR4_IIR_FLAG    0x100
#define 	PWM_MR5_IIR_FLAG    0x200
#define 	PWM_MR6_IIR_FLAG	0x400
#define 	PWM_CAP0_IIR_FLAG	0x10
#define 	PWM_CAP1_IIR_FLAG	0x20

/*  Defines */

#define DEDO_PULGAR                 10
#define DEDO_INDICE                 11
#define DEDO_MAYOR                  12
#define DEDO_ANULAR                 13
#define DEDO_MENOR                  14
#define CANT_DEDOS                  5

#define CANAL_1                     0
#define CANAL_2                     1
#define CANAL_3                     2
#define CANAL_4                     3
#define CANAL_5                     4
#define CANAL_6                     5
#define CANT_CANALES                6

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/

extern volatile uint32_t Buffer_TH[];
extern volatile uint8_t Buffer_NEW_TH[];
extern volatile uint8_t Buffer_NEW_ENABLE[];
extern volatile uint8_t Buffer_NEW_DISABLE[];

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/

/*  FUNCIONES PARA TPO_INFO_2    */

void PWM1_Init_5Canales( void );
void PWM1_Config_Canal( uint8_t Canal, uint32_t Valor_Inicial );

/*  ABAJO, TODAS LAS NO USADAS PARA EL TPO_INFO_2   */

void PWM1_Actualizar_5Canales( void );

#endif /* end DR_PWM_H_ */
