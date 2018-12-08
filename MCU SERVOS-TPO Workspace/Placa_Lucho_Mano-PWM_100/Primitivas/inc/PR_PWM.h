/*******************************************************************************************************************************//**
 *
 * @file		PR_PWM.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		28 de oct. de 2018
 * @author		Saldivia, Luciano
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef PR_PWM_H_
#define PR_PWM_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/

#include "DR_PWM.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/

#define SUAVIZAR_MODO_EXPONENCIAL	1	// Distintos de 0 !!!!
#define SUAVIZAR_MODO_LINEAL		2
#define SUAVIZAR_MODO_ELIPTICO		3

// para el SysTick
#define EXPONENCIAL	10
#define	LINEAL		11
#define	ELIPTICO	12

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

typedef struct{
    uint16_t Pulgar;
    uint16_t Indice;
    uint16_t Mayor;
    uint16_t Anular;
    uint16_t Menor;
}Lecturas_Mano_1000;

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES (para incluir en otros .c)
 **********************************************************************************************************************************/

extern volatile uint8_t f_Stop_Suave;

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/

/*  FUNCIONES PARA TPO_INFO_2    */

void PWM_Set_Lecturas( Lecturas_Mano_1000 *Lecturas );
//uint16_t Convertir( uint16_t Lectura_4096 );
void PWM_Get_Lecturas( Lecturas_Mano_1000 *Lecturas );
void PWM_Enable_5_Channels( void );
void PWM_Disable_5_Channels( void );
//void PWM_Stop_Suave_5_Channels( uint8_t Modo );
//void Tick_Call_Back_Stop_Suave_Exponencial( void );
//void Tick_Call_Back_Stop_Suave_Lineal( void );
//void Tick_Call_Back_Stop_Suave_Eliptico( void );



//  Funciones para el CANAL PWM1_1

//void PWM_1_Set( uint32_t Valor_Lectura_4096 );
//uint32_t PWM_1_Get( void );
//void PWM_1_Start( void );
//void PWM_1_Stop( void );


//  Funciones para el CANAL PWM1_2

//void PWM_2_Set( uint32_t Valor_Lectura_4096 );
//uint32_t PWM_2_Get( void );
//void PWM_2_Start( void );
//void PWM_2_Stop( void );


//  Funciones para el CANAL PWM1_3

//void PWM_3_Set( uint32_t Valor_Lectura_4096 );
//uint32_t PWM_3_Get( void );
//void PWM_3_Start( void );
//void PWM_3_Stop( void );


//  Funciones para el CANAL PWM1_4
//
//void PWM_4_Set( uint32_t Valor_Lectura_4096 );
//uint32_t PWM_4_Get( void );
//void PWM_4_Start( void );
//void PWM_4_Stop( void );


//  Funciones para el CANAL PWM1_5

//void PWM_5_Set( uint32_t Valor_Lectura_4096 );
//uint32_t PWM_5_Get( void );
//void PWM_5_Start( void );
//void PWM_5_Stop( void );


/*  ABAJO, TODAS LAS NO USADAS PARA EL TPO_INFO_2   */

//void PWM_Start_All_Channels( void );
//void PWM_Stop_All_Channels( void );

//  Funciones para el CANAL PWM1_6

//void PWM_6_Set( uint32_t Valor_Lectura_4096 );
//uint32_t PWM_6_Get( void );
//void PWM_6_Start( void );
//void PWM_6_Stop( void );







#endif /* PR_PWM_H_ */