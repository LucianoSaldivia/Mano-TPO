/*******************************************************************************************************************************//**
 *
 * @file		PR_ADC_MEDIANA.c
 * @brief		--Descripción del Módulo--
 * @date		14/10/2018
 * @author		Esteban Chiama
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/

#include <PR_ADC_MEDIANA.h>

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

typedef struct SAMPLES{
	volatile uint16_t ch0[SIZE];
	volatile uint16_t ch1[SIZE];
	volatile uint16_t ch2[SIZE];
	volatile uint16_t ch3[SIZE];
	volatile uint16_t ch4[SIZE];
}samples_t;

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

static volatile uint8_t inxBuffers = 0;			// inxBuffers es la posición en todos los buffers

static volatile samples_t Samples;

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

uint8_t GetBufferStatus(void);
void Enlistar(void);

/***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

uint8_t GetBufferStatus(void){

	uint8_t bufferStatus = ENLISTANDO;

	if ( inxBuffers == SIZE ){
		inxBuffers = 0;
		bufferStatus = VECTORES_LLENOS;
	}

	return bufferStatus;
}

void Enlistar(void){

	uint16_t adc_samples_cpy[QTY_INPUT_CHANNELS];
	uint8_t i=0;

	// copio las muestras del adc a una variable auxiliar
	while(i<QTY_INPUT_CHANNELS){
		adc_samples_cpy[i] = ADC_Samples[i];
		i++;
	}

	Samples.ch0[inxBuffers] = adc_samples_cpy[0];
	Samples.ch1[inxBuffers] = adc_samples_cpy[1];
	Samples.ch2[inxBuffers] = adc_samples_cpy[2];
	Samples.ch3[inxBuffers] = adc_samples_cpy[3];
	Samples.ch4[inxBuffers] = adc_samples_cpy[4];

	inxBuffers++;
}

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/

uint8_t Preparar_y_Filtrar( filtered_Samples_t *MuestrasEfectivas ){
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

void ResetBuffers( void ){
	// Simplemente que se vuelva a escribir en los buffers desde la posición 0
	inxBuffers = 0;
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


filtered_Samples_t Mediana_de_Buffers(){
	filtered_Samples_t MuestrasEfectivas;

	// Ordenamos los vectores
	bubble(Samples.ch0, SIZE);
	bubble(Samples.ch1, SIZE);
	bubble(Samples.ch2, SIZE);
	bubble(Samples.ch3, SIZE);
	bubble(Samples.ch4, SIZE);

	// Calculamos la media

	MuestrasEfectivas.ch0 = ( Samples.ch0[(SIZE/2)-1] + Samples.ch0[SIZE/2] ) / 2;

	MuestrasEfectivas.ch1 = ( Samples.ch1[(SIZE/2)-1] + Samples.ch1[SIZE/2] ) / 2;

	MuestrasEfectivas.ch2 = ( Samples.ch2[(SIZE/2)-1] + Samples.ch2[SIZE/2] ) / 2;

	MuestrasEfectivas.ch3 = ( Samples.ch3[(SIZE/2)-1] + Samples.ch3[SIZE/2] ) / 2;

	MuestrasEfectivas.ch4 = ( Samples.ch4[(SIZE/2)-1] + Samples.ch4[SIZE/2] ) / 2;

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
