/* Recordar que según nuestra definición, los buffers y entradas se corresponden como:
 *
 * H[15] = AD0.0 = meñique
 * H[16] = AD0.1 = anular
 * H[17] = AD0.2 = medio
 * H[18] = AD0.3 = índice
 * H[19] = AD0.4 = pulgar
 *
**/

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

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

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

volatile uint32_t aux_cont=0;

void Enlistar( void ){

	uint16_t sample = ADC_sample;

	aux_cont++;
	if(aux_cont >= 25){
		aux_cont=0;
	}

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


Muestras_Medias_t Mediana_de_Buffers( uint16_t length ){

	Muestras_Medias_t MuestrasEfectivas;

	// Ordenamos los vectores
	bubble(BufferInput0,length);
	bubble(BufferInput1,length);
	bubble(BufferInput2,length);
	bubble(BufferInput3,length);
	bubble(BufferInput4,length);

	// Calculamos la media

	MuestrasEfectivas.m0 = ( BufferInput0[(length/2)-1] + BufferInput0[length/2] ) / 2;

	MuestrasEfectivas.m1 = ( BufferInput1[(length/2)-1] + BufferInput1[length/2] ) / 2;

	MuestrasEfectivas.m2 = ( BufferInput2[(length/2)-1] + BufferInput2[length/2] ) / 2;

	MuestrasEfectivas.m3 = ( BufferInput3[(length/2)-1] + BufferInput3[length/2] ) / 2;

	MuestrasEfectivas.m4 = ( BufferInput4[(length/2)-1] + BufferInput4[length/2] ) / 2;

	return MuestrasEfectivas;
}


// Función para obtener la mediana de un buffer
// Requisitos: buffer de tamaño par y tipo de dato uint16_t
uint32_t Mediana_Buffer( volatile uint16_t *buffer, uint16_t length ){

	uint32_t valor_mediana;

	// Ordenamos el vector de menor a mayor
	bubble(buffer,length);

	// Calculamos la media
	valor_mediana = ( *(buffer+(length/2)-1) + *(buffer+(length/2)) ) / 2;
	// valor_mediana = ( buffer[(length/2)-1] + buffer[length/2] ) / 2;

	return valor_mediana;
}


uint8_t Preparar_y_Filtrar( Muestras_Medias_t *MuestrasEfectivas ){

	uint8_t bufferStatus;
	uint8_t f_Filter_Done = 0;

	bufferStatus = GetBufferStatus();
	if( bufferStatus ==  VECTORES_LLENOS ){
		*MuestrasEfectivas = Mediana_de_Buffers(SIZE);
		f_Filter_Done = 1;
	}

	Enlistar();

	return f_Filter_Done;
}