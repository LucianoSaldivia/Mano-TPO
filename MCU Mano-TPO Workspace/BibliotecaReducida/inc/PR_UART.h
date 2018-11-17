/*******************************************************************************************************************************//**
 *
 * @file		PR_UART.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		5 de oct. de 2017
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef PRIMITIVAS_PR_UART_H_
#define PRIMITIVAS_PR_UART_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "Config.h"
#include "Tipos.h"
/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#ifdef	MODULO_UART_ACTIVO
/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/
#define UART0	0
#define UART1	1

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
// extern tipo nombreVariable;

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
/**
	\fn int16_t Transmitir ( uint8_t com , const void * datos , uint8_t cant)
	\brief despacha los datos a transmitir
 	\author Ing. Marcelo Trujillo
 	\date 5 de oct. de 2017
 	\param [in] uint8_t com: Puerto que sera utilizado
	\param [in] const void * datos: datos a transmitir
	\param [in] uint8_t cant: cantidad de datos a transmitir
	\return 0 por exito, -1 por Error (datos exedidos)
*/
int16_t Transmitir ( uint8_t com , const void * datos , uint8_t cant );

/**
	\fn int16_t Mensajes (uint8_t com, void *buff, uint16_t max)
	\brief Lee del buffer de recepcion la cantidad de bytes (como maximo) pedidos
 	\author Augusto Santini
 	\date 21 de oct. de 2018
 	\param [in] uint8_t com: Puerto que sera utilizado
 	\param [in] void *buff: Buffer donde guardar los datos leidos, debe tener la memoria reservada
	\param [in] uint16_t max: Maxima cantidad de bytes a sacar del buffer
	\return Cantidad de bytes leidos, -1 por error
*/
int16_t Mensajes(uint8_t com, void *buff, uint16_t max);

/**
	\fn uint8_t estadoTx (uint8_t com)
	\brief Devuelve el estado del buffer de transmision
 	\author Augusto Santini
 	\date 21 de oct. de 2018
 	\param [in] uint8_t com: Puerto que sera utilizado
	\return Estado del buffer de transmision, 1 si esta con datos, 0 si esta vacio
*/
uint8_t estadoTx(uint8_t com);

#endif /* PRIMITIVAS_PR_UART_H_ */
#endif
