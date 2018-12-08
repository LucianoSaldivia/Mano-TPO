/*
 * pr_muestreo_5canales.c
 *
 *  Created on: Oct 14, 2018
 *      Author: cha
 */

#include "pr_muestreo_5canales.h"

/* Recordar que según nuestra definición, los buffers y entradas se corresponden como:
** Input0 : Pulgar (EA2)
** Input1 : Indice (EA1)
** Input2:	Medio (EA0)
** Input3:	Anular (H[18])
** Input4:	Menique (H[19])
 */

volatile uint16_t BufferInput0[SIZE];
volatile uint16_t BufferInput1[SIZE];
volatile uint16_t BufferInput2[SIZE];
volatile uint16_t BufferInput3[SIZE];
volatile uint16_t BufferInput4[SIZE];

static uint8_t inxBuffers = 0;			// inxBuffers es la posición en todos los buffers
static uint8_t BufferNumber = 0;		// BufferNumber es número de buffer....genio

void ResetBuffers( void ){

	// Simplemente que se vuelva a escribir desde el Buffer0 en posición 0
	BufferNumber = 0;
	inxBuffers = 0;

}

uint8_t GetBufferStatus( void ){

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

/* Desde la MdE, se llamaría a Enlistado en algo así:

if ADC_dato_disponible

	A = GetBufferStatus()
	if( A == VECTORES_LLENOS ){
		MuestrasListasParaEnviar = GetMedias_Buffers();
	}

*/


Muestras_Medias_t GetMedias_Buffers( void ){

	Muestras_Medias_t EffectiveSamples;

	// Ordenamos los vectores
	bubble(BufferInput0,SIZE);
	bubble(BufferInput1,SIZE);
	bubble(BufferInput2,SIZE);
	bubble(BufferInput3,SIZE);
	bubble(BufferInput4,SIZE);

	// Calculamos la media

	EffectiveSamples.m0 = ( BufferInput0[3] + BufferInput0[4] + BufferInput0[5] + BufferInput0[6] ) / 4;

	EffectiveSamples.m1 = ( BufferInput1[3] + BufferInput1[4] + BufferInput1[5] + BufferInput1[6] ) / 4;

	EffectiveSamples.m2 = ( BufferInput2[3] + BufferInput2[4] + BufferInput2[5] + BufferInput2[6] ) / 4;

	EffectiveSamples.m3 = ( BufferInput3[3] + BufferInput3[4] + BufferInput3[5] + BufferInput3[6] ) / 4;

	EffectiveSamples.m4 = ( BufferInput4[3] + BufferInput4[4] + BufferInput4[5] + BufferInput4[6] ) / 4;

	return EffectiveSamples;
}


/* Funcion bubble, que ordena un vector de menor a mayor con el metodo de burbujeo.*/
void bubble(int *vector, int size){

	int aux; //para el swap.
	int i, j;

	for(j=0; j<size-1; j++)
	{
		for(i=0; i<size-1-j; i++)
		{
			if(vector[i]>vector[i+1])
			{
				aux = vector[i+1];
				vector[i+1] = vector[i];
				vector[i] = aux;
			}
		}
	}
}
