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

#ifndef PRIMITIVAS_PR_SYSTICK_H_
#define PRIMITIVAS_PR_SYSTICK_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "Config.h"
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

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
/**
	\fn void setTickCallback(void)
	\brief Enganche al tick
 	\details Configura la funcion a llamar desde el systick (forma de colgarse sin tocar la libreria)
	\param [in] void *nuevoCallback(void): Funcion a llamar desde el systick
	\return void
*/
void setTickCallback(void (*nuevoCallback)(void));

#endif /* PRIMITIVAS_PR_SYSTICK_H_ */