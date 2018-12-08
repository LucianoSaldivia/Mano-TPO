/*
 * AP_muestreo_mano.c
 *
 *  Created on: Oct 22, 2018
 *      Author: cha
 */


#include "pr_muestreo_5canales.h"


void Preparar_y_Enviar( void ){

	uint8_t bufferStatus, flag_Enviar = 0;
	Muestras_Medias_t MuestrasListasParaEnviar;

	bufferStatus = GetBufferStatus();
	if( bufferStatus ==  VECTORES_LLENOS ){
		MuestrasListasParaEnviar = GetMedias_Buffers();
		flag_Enviar = 1;
	}

	Enlistar();

	if( flag_Enviar == 1 ){
		// transmito la trama con una nueva mano
		EnviarMano( MuestrasListasParaEnviar );
	}

}


void EnviarMano( Muestras_Medias_t ManoMuestreada ) {

	PushTx('#');

	PushTx( (uint8_t) ((ManoMuestreada.m0 >> 8) & 0xFF) );	// envío primero los 4 bits más significativos
	PushTx( (uint8_t) (ADC_sample & 0xFF) );								// envío los 8 restantes

	PushTx(',');

	PushTx( (uint8_t) ((ManoMuestreada.m1 >> 8) & 0xFF) );	// envío primero los 4 bits más significativos
	PushTx( (uint8_t) (ADC_sample & 0xFF) );								// envío los 8 restantes

	PushTx(',');

	PushTx( (uint8_t) ((ManoMuestreada.m2 >> 8) & 0xFF) );	// envío primero los 4 bits más significativos
	PushTx( (uint8_t) (ADC_sample & 0xFF) );								// envío los 8 restantes

	PushTx(',');

	PushTx( (uint8_t) ((ManoMuestreada.m3 >> 8) & 0xFF) );	// envío primero los 4 bits más significativos
	PushTx( (uint8_t) (ADC_sample & 0xFF) );								// envío los 8 restantes

	PushTx(',');

	PushTx( (uint8_t) ((ManoMuestreada.m4 >> 8) & 0xFF) );	// envío primero los 4 bits más significativos
	PushTx( (uint8_t) (ADC_sample & 0xFF) );								// envío los 8 restantes

	PushTx('$');

	return;
}

