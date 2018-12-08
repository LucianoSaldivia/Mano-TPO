/*
 * AP_Controlador.h
 *
 *  Created on:
 *      Author:
 */

#ifndef INC_AP_CONTROLADOR_H_
#define INC_AP_CONTROLADOR_H_

#include "stdio.h"
#include "pr_muestreo_5canales.h"
#include "FW_SysTick.h"
#include "FW_IO.h"
#include "PR_Serie.h"
#include "PR_LCD.h"

// Constantes para el estado del medidor
#define MEDIDOR_RESET		0
#define	MEDIDOR_INACTIVO	1
#define	MEDIDOR_ACTIVO		2

// Constante para MdE UART Rx
#define ESPERANDO_TRAMA		0
#define RECIBIENDO_TRAMA	1
#define MAX_TRAMA_RX	8

// Constantes para el command
#define NO_COMMAND			0
#define START_ADC			1
#define STOP_ADC			2
#define CONFIG_SR			3
#define CONFIG_INPUT		4
#define SEND_TEST_SIGNAL_1	5
#define SEND_TEST_SIGNAL_2	6
#define SEND_TEST_SIGNAL_3	7

// Constantes para indicar la tx status de la señal de prueba
#define TX_DOING	0
#define TX_DONE		1

// Funciones
void Controlador(void);
void RX_Mensajes(void);
void leer_comandos( const char msg_rx[] );
uint8_t tx_Test_Signal_1( void );
uint8_t tx_Test_Signal_2( void );

#endif /* INC_AP_CONTROLADOR_H_ */
