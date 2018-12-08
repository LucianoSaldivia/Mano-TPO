/*******************************************************************************************************************************//**
 *
 * @file		PR_String.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		14 de nov. de 2017
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef PRIMITIVAS_INC_PR_STRINGS_H_
#define PRIMITIVAS_INC_PR_STRINGS_H_

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
extern char Mensaje0 [];
extern char Mensaje1 [];

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
/**
	@fn  		void Itoa( char* str, int32_t Val )
	@brief 		convierte un entero en un string
 	@author 	Ing. Marcelo Trujillo
 	@date 		25/10/17
 	@param 		[out] string: direcion de comienzo de la string eb�n donde se deja el dato convertido
 	@param 		[in ] Val: valor a convertir
	@return void
*/
void Itoa( char* str , int32_t Val );

/**
	@fn  		void Strcat ( char* d , char* o )
	@brief 		concatena dos strings d + o
 	@author 	Ing. Marcelo Trujillo
 	@date 		25/10/17
 	@param 		[out] d: destino de la concatenacion
 	@param 		[in ] o: origen de la string a concatenar
	@return void
*/
void Strcat ( char* , char*  );

/**
	@fn  		void Strcpy ( char* d , char* o )
	@brief 		Copia una string sobre otra
 	@author 	Ing. Marcelo Trujillo
 	@date 		25/10/17
 	@param 		[out] d: destino de la copia
 	@param 		[in ] o: fuente de la copia
	@return void
*/
void Strcpy ( char* , char* );

/**
	@fn  		void Strformat ( char* d , char f , uint8_t n)
	@brief 		Completa al ppio de la string con el caracter enviado en f
 	@author 	Ing. Marcelo Trujillo
 	@date 		25/10/17
 	@param 		[out] d: String a formatear
 	@param 		[in ] f: caracter con el que se completara
 	@param 		[in ] n: tama�o final de la string
	@return void
*/
void Strformat ( char*  , char  , uint8_t );

#endif /* PRIMITIVAS_INC_PR_STRINGS_H_ */
