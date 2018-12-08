/*******************************************************************************************************************************//**
 *
 * @file		PR_Timers.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		2 de jun. de 2017
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef PRIMITIVAS_PR_TIMERS_H_
#define PRIMITIVAS_PR_TIMERS_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "Config.h"
#include "Tipos.h"
/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#ifdef	MODULO_TIMERS_ACTIVO

#define 	DEC			0
#define 	SEG			1
#define 	MIN			2

#define 	RUN			0
#define 	PAUSE		1

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
/**
	\fn void TimerStart(uint8_t event, timer_t t, void (*handler)(void))
	\brief Inicia un timer
 	\details Inicia el timer \a e al transcurrir el tiempo especificado por \a t se llama a la funcion apuntada por \a handler
 	\param [in] event Numero de evento entre 0 y 31
 	\param [in] t Tiempo del evento. Dependiente de la base de tiempos
 	\param [in] handler Callback del evento
	\return void
*/
void TimerStart(uint8_t event, uint32_t time, Timer_Handler handler , uint8_t base );

/**
	\fn void SetTimer( uint8_t event , timer_t t )
	\brief Inicia un timer
 	\details Reinicia el timer con el valor t (no lo resetea)
 	\param [in] event Numero de evento entre 0 y 31
 	\param [in] t Tiempo del evento. Dependiente de la base de tiempos
 	\return void
*/
void SetTimer( uint8_t event, uint32_t time );

/**
	\fn  GetTimer( uint8_t event )
	\brief Toma el valor al vuelo del timer en cuestion
 	\details Lee el timer
 	\param [in] event Numero de evento entre 0 y 31
 	\return valor del timer
*/
uint32_t GetTimer( uint8_t event );

/**
	\fn  StandByTimer( uint8_t event , uint8_t accion)
	\brief Detiene/Arranca el timer, NO lo resetea
 	\details lo pone o lo saca de stand by
 	\param [in] event Numero de evento entre 0 y 31
 	\param [in] accion RUN lo arranca, PAUSE lo pone en stand by
 	\return void
*/
void StandByTimer( uint8_t event , uint8_t accion);

/**
	\fn void Timer_Stop(Eventos e)
	\brief Detiene un timer
 	\details Detiene el timer \a e
 	\param [in] e Numero de evento entre 0 y 31
	\return void
*/
void TimerStop(uint8_t event);

/**
	\fn void Timer_Close(void)
	\brief Detiene los timers
 	\details Detiene todos los timers
	\return void
*/
void TimerClose(void);

/**
	\fn void Timer_Event(void)
	\brief Chequeo de timers vencidos
 	\details Llama a los callbacks de los timers vencidos. Debe llamarse desde el lazo principal del programa
	\return void
*/
void TimerEvent(void);

#endif

#endif /* PRIMITIVAS_PR_TIMERS_H_ */
