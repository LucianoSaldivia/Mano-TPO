/*
 * pr_muestreo_5canales.h
 *
 *  Created on: Oct 14, 2018
 *      Author: cha
 */

#ifndef INC_PR_MUESTREO_5CANALES_H_
#define INC_PR_MUESTREO_5CANALES_H_

#include "../../Drivers/inc/dr_ADC_5canales_timer.h"

typedef struct MUESTRAS_MEDIAS{
	uint16_t m0;
	uint16_t m1;
	uint16_t m2;
	uint16_t m3;
	uint16_t m4;
}Muestras_Medias_t;

#define SIZE			10

#define VECTORES_LLENOS	1
#define ENLISTANDO		2

void ResetBuffers( void );
void Enlistar( void );
Muestras_Medias_t GetMedias_Buffers( void );
void bubble(int *vector, int size);


#endif /* INC_PR_MUESTREO_5CANALES_H_ */
