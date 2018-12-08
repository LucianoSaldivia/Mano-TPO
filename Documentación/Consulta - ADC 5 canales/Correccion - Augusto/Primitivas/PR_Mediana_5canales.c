/* Recordar que según nuestra definición, los buffers y entradas se corresponden como:
** Input0 : Pulgar (EA2)
** Input1 : Indice (EA1)
** Input2:	Medio (EA0)
** Input3:	Anular (H[18])
** Input4:	Menique (H[19])
 */


/*******************************************************************************************************************************//**
 *
 * @file		PR_Mediana_5canales.c
 * @brief		--Descripción del Módulo--
 * @date		14/10/2018
 * @author		Esteban Chiama
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/


#include "PR_Mediana_5canales.h"


/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/


static uint8_t inxBuffers = 0;			// inxBuffers es la posición en todos los buffers
static uint8_t BufferNumber = 0;		// BufferNumber es número de buffer....genio


volatile uint16_t BufferInput0[SIZE];
volatile uint16_t BufferInput1[SIZE];
volatile uint16_t BufferInput2[SIZE];
volatile uint16_t BufferInput3[SIZE];
volatile uint16_t BufferInput4[SIZE];


/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/


void bubble(volatile uint16_t *vector, int size);


 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/


/* Funcion bubble, que ordena un vector de menor a mayor con el metodo de burbujeo.*/
void bubble(volatile uint16_t *vector, int size) {

	int aux; //para el swap.
	int i, j;

	for(j=0; j<size-1; j++)	{

		for(i=0; i<size-1-j; i++) {

			if(vector[i]>vector[i+1]) {
				aux = vector[i+1];
				vector[i+1] = vector[i];
				vector[i] = aux;
			}

		}

	}
}


 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/


void ResetBuffers( void ){

	// Simplemente que se vuelva a escribir desde el Buffer0 en posición 0
	BufferNumber = 0;
	inxBuffers = 0;

}


uint8_t GetBufferStatus(void){

	uint8_t bufferStatus = ENLISTANDO;

	if ( inxBuffers == SIZE ){
		inxBuffers = 0;
		bufferStatus = VECTORES_LLENOS;
	}

	return bufferStatus;
}


void Enlistar( void ){

	uint16_t sample = ADC_sample;

	switch( BufferNumber ){
		case 0:
			BufferInput0[inxBuffers] = sample;
			BufferNumber++;
			break;
		case 1:
			BufferInput1[inxBuffers] = sample;
			BufferNumber++;
			break;
		case 2:
			BufferInput2[inxBuffers] = sample;
			BufferNumber++;
			break;
		case 3:
			BufferInput3[inxBuffers] = sample;
			BufferNumber++;
			break;
		case 4:
			BufferInput4[inxBuffers] = sample;
			BufferNumber=0;
			inxBuffers++;
			break;
	}

}


Muestras_Medias_t Mediana_de_Buffers( void ){

	Muestras_Medias_t MuestrasEfectivas;

	// Ordenamos los vectores
	bubble(BufferInput0,SIZE);
	bubble(BufferInput1,SIZE);
	bubble(BufferInput2,SIZE);
	bubble(BufferInput3,SIZE);
	bubble(BufferInput4,SIZE);

	// Calculamos la media

	MuestrasEfectivas.m0 = ( BufferInput0[4] + BufferInput0[5] ) / 2;

	MuestrasEfectivas.m1 = ( BufferInput1[4] + BufferInput1[5] ) / 2;

	MuestrasEfectivas.m2 = ( BufferInput2[4] + BufferInput2[5] ) / 2;

	MuestrasEfectivas.m3 = ( BufferInput3[4] + BufferInput3[5] ) / 2;

	MuestrasEfectivas.m4 = ( BufferInput4[4] + BufferInput4[5] ) / 2;

	return MuestrasEfectivas;
}
