/*******************************************************************************************************************************//**
 *
 * @file		PR_Eçntradas.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		14 de nov. de 2017
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef PRIMITIVAS_INC_PR_ENTRADAS_H_
#define PRIMITIVAS_INC_PR_ENTRADAS_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "Tipos.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

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
	\fn  uint8_t Entradas ( uint8_t nEntrada )
	\brief Valor de una de las entradas digitales
 	\author Ing. Marcelo Trujillo
 	\date 14 de nov. de 2017
 	\param [in] numero de entrada
		<ul>
			<li> Numeros de entrada en las siguientes macros
			<ol>
			<li> ENTRADA0 : 0
			<li> ENTRADA1 : 1
			<li> ENTRADA2 : 2
			</ol>
		</ul>
	\return tipo y descripcion de retorno
*/
uint8_t Entradas ( uint8_t nEntrada );

#endif /* PRIMITIVAS_INC_PR_ENTRADAS_H_ */