/*******************************************************************************************************************************//**
 *
 * @file		AP_Guante_Muestreo.c
 * @brief		--Descripción del Módulo--
 * @date		22/10/2018
 * @author		Esteban Chiama
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/

#include <AP_Guante_Muestreo.h>

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

// cantidad de muestras a tomar para calibrar, por cada dedo
#define CAL_SIZE	20

// estado_calibrar
#define	CALIB_RESET			0
#define CALIB_INACTIVE		1
#define CALIB_PUSH			2
#define	CALIB_SAMPLING		3
#define CALIB_PROCESS		4
#define CALIB_DONE			5

// estado_secuencia
#define	NO_SEQUENCE				0
#define	WAIT_OPEN_HAND			1
#define	WAIT_CLOSED_HAND		2
#define	WAIT_CLOSED_THUMB		3
#define	SAMPLE_OPEN_HAND		4
#define	SAMPLE_CLOSED_HAND		6
#define	SAMPLE_CLOSED_THUMB		7

// conversión a valor para PWM
#define MAX_PWM		1000
#define MIN_PWM		0

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

typedef struct MANO_CALIBRACION{
	uint16_t Menique[CAL_SIZE];
	uint16_t Anular[CAL_SIZE];
	uint16_t Medio[CAL_SIZE];
	uint16_t Indice[CAL_SIZE];
	uint16_t Pulgar[CAL_SIZE];
}CAL_Mano_t;

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

volatile uint8_t f_Start_Calibration = 0;

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

static volatile uint8_t CAL_inxBuffers = 0;

volatile CAL_Mano_t CAL_Mano_Abierta;
volatile CAL_Mano_t CAL_Mano_Cerrada;
volatile CAL_Mano_t CAL_Pulgar_Cerrado;

static volatile Mano_t CAL_rango;
static volatile Mano_t CAL_Minimos;


/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

uint16_t modulo(uint16_t a, uint16_t b, volatile uint16_t *Min);
void NormalizarMano( Mano_t *ManoFiltrada );
void ObtenerManoPWM( Mano_t *ManoNormalizada );

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

// Devuelve el módulo de la resta y además coloca en Min la variable de menor valor
uint16_t modulo(uint16_t a, uint16_t b, volatile uint16_t *Min){
	uint16_t abs;

	if( a > b ){
		abs = a - b;
		*Min = b;
	}
	else{
		abs = b - a;
		*Min = a;
	}

	return abs;
}

void NormalizarMano( Mano_t *ManoFiltrada ){

	// Con protección por si "satura" por debajo del mínimo o por arriba del rango, para evitar overflow y evitar valores por arriba
	// de 1000 para el PWM

	// Dedo Meñique
	if( ManoFiltrada->Menique < CAL_Minimos.Menique ){
		ManoFiltrada->Menique = 0;
	}
	else{
		ManoFiltrada->Menique = ManoFiltrada->Menique - CAL_Minimos.Menique;

		if( ManoFiltrada->Menique > CAL_rango.Menique ){
			ManoFiltrada->Menique = CAL_rango.Menique;
		}
	}

	// Dedo Anular
	if( ManoFiltrada->Anular < CAL_Minimos.Anular ){
		ManoFiltrada->Anular = 0;
	}
	else{
		ManoFiltrada->Anular = ManoFiltrada->Anular - CAL_Minimos.Anular;

		if( ManoFiltrada->Anular > CAL_rango.Anular ){
			ManoFiltrada->Anular = CAL_rango.Anular;
		}
	}

	// Dedo Medio
	if( ManoFiltrada->Medio < CAL_Minimos.Medio ){
		ManoFiltrada->Medio = 0;
	}
	else{
		ManoFiltrada->Medio = ManoFiltrada->Medio - CAL_Minimos.Medio;

		if( ManoFiltrada->Medio > CAL_rango.Medio ){
			ManoFiltrada->Medio = CAL_rango.Medio;
		}
	}

	// Dedo Indice
	if( ManoFiltrada->Indice < CAL_Minimos.Indice ){
		ManoFiltrada->Indice = 0;
	}
	else{
		ManoFiltrada->Indice = ManoFiltrada->Indice - CAL_Minimos.Indice;

		if( ManoFiltrada->Indice > CAL_rango.Indice ){
			ManoFiltrada->Indice = CAL_rango.Indice;
		}
	}

	// Dedo Pulgar
	if( ManoFiltrada->Pulgar < CAL_Minimos.Pulgar ){
		ManoFiltrada->Pulgar = 0;
	}
	else{
		ManoFiltrada->Pulgar = ManoFiltrada->Pulgar - CAL_Minimos.Pulgar;

		if( ManoFiltrada->Pulgar > CAL_rango.Pulgar ){
			ManoFiltrada->Pulgar = CAL_rango.Pulgar;
		}
	}

}

void ObtenerManoPWM( Mano_t *ManoNormalizada ){

	ManoNormalizada->Menique = (ManoNormalizada->Menique *  MAX_PWM) / CAL_rango.Menique;
	ManoNormalizada->Anular = (ManoNormalizada->Anular * MAX_PWM) / CAL_rango.Anular;
	ManoNormalizada->Medio = (ManoNormalizada->Medio * MAX_PWM) / CAL_rango.Medio;
	ManoNormalizada->Indice = (ManoNormalizada->Indice * MAX_PWM) / CAL_rango.Indice;
	ManoNormalizada->Pulgar = (ManoNormalizada->Pulgar * MAX_PWM) / CAL_rango.Pulgar;

}

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/

void Preparar_y_Enviar( void ){

	uint8_t f_Enviar = 0;
	Mano_t Mano;

	f_Enviar = Preparar_y_Filtrar( (filtered_Samples_t *) &Mano );

	if ( f_Enviar ){
		// transmito la trama con una nueva mano
		NormalizarMano(&Mano);
		ObtenerManoPWM(&Mano);
		EnviarMano(Mano);

//		EnviarDedo(Mano.Menique);			// CLAVADO EN 0
//		EnviarDedo(Mano.Anular);			// CLAVADO EN 4095
//		EnviarDedo(Mano.Medio);				// ANDA BARBARO
//		EnviarDedo(Mano.Indice);			// ANDA BARBARO
//		EnviarDedo(Mano.Pulgar);			// ANDA BARBARO
	}
}

void EnviarDedo( uint16_t dedo ){
	U1_PushTx('#');
	U1_PushTx( (uint8_t) ((dedo >> 8) & 0xF) );
	U1_PushTx( (uint8_t) (dedo & 0xFF) );
	U1_PushTx('$');
}

void EnviarMano( Mano_t Mano ) {

	U1_PushTx('#');

	U1_PushTx( (uint8_t) ((Mano.Menique >> 8) & 0xF) );		// Envío los 8 bits (en realidad 4, el ADC es de 12bits) más significativos
	U1_PushTx( (uint8_t) (Mano.Menique & 0xFF) );			// Envío los 8 bits menos significativos

	U1_PushTx(',');

	U1_PushTx( (uint8_t) ((Mano.Anular >> 8) & 0xF) );
	U1_PushTx( (uint8_t) (Mano.Anular & 0xFF) );

	U1_PushTx(',');

	U1_PushTx( (uint8_t) ((Mano.Medio >> 8) & 0xF) );
	U1_PushTx( (uint8_t) (Mano.Medio & 0xFF) );

	U1_PushTx(',');

	U1_PushTx( (uint8_t) ((Mano.Indice >> 8) & 0xF) );
	U1_PushTx( (uint8_t) (Mano.Indice & 0xFF) );

	U1_PushTx(',');

	U1_PushTx( (uint8_t) ((Mano.Pulgar >> 8) & 0xF) );
	U1_PushTx( (uint8_t) (Mano.Pulgar & 0xFF) );

	U1_PushTx('$');

	return;
}

uint8_t Preparar_Calibracion( const uint8_t secuencia ){

	Mano_t Mano;
	uint8_t f_Enlistar_Mano = 0;
	uint8_t f_Status_Cal = 0;

	f_Enlistar_Mano = Preparar_y_Filtrar( (filtered_Samples_t *) &Mano );

	if ( f_Enlistar_Mano ){

		switch (secuencia){
			case SAMPLE_OPEN_HAND:
				CAL_Mano_Abierta.Menique[CAL_inxBuffers] = Mano.Menique;
				CAL_Mano_Abierta.Anular[CAL_inxBuffers] = Mano.Anular;
				CAL_Mano_Abierta.Medio[CAL_inxBuffers] = Mano.Medio;
				CAL_Mano_Abierta.Indice[CAL_inxBuffers] = Mano.Indice;
				CAL_Mano_Abierta.Pulgar[CAL_inxBuffers] = Mano.Pulgar;
				break;

			case SAMPLE_CLOSED_HAND:
				CAL_Mano_Cerrada.Menique[CAL_inxBuffers] = Mano.Menique;
				CAL_Mano_Cerrada.Anular[CAL_inxBuffers] = Mano.Anular;
				CAL_Mano_Cerrada.Medio[CAL_inxBuffers] = Mano.Medio;
				CAL_Mano_Cerrada.Indice[CAL_inxBuffers] = Mano.Indice;
//				CAL_Mano_Cerrada.Pulgar[CAL_inxBuffers] = Mano.Pulgar;
				// El pulgar de la mano cerrada no nos interesa
				break;

			case SAMPLE_CLOSED_THUMB:
				// Del pulgar cerrado solamente nos interesa el pulgar
//				CAL_Pulgar_Cerrado.Menique[CAL_inxBuffers] = Mano.Menique;
//				CAL_Pulgar_Cerrado.Anular[CAL_inxBuffers] = Mano.Anular;
//				CAL_Pulgar_Cerrado.Medio[CAL_inxBuffers] = Mano.Medio;
//				CAL_Pulgar_Cerrado.Indice[CAL_inxBuffers] = Mano.Indice;
				CAL_Pulgar_Cerrado.Pulgar[CAL_inxBuffers] = Mano.Pulgar;
				break;

			default:
				break;
		}

		CAL_inxBuffers++;
		if( CAL_inxBuffers == CAL_SIZE ){
			f_Status_Cal = 1;
			CAL_inxBuffers = 0;
		}
	}

	return f_Status_Cal;
}

void Calibrar( void ){

	Mano_t Abierta_Filtrada, Cerrada_Filtrada;

	// Ordeno los vectores y obtengo su mediana

		// 1. Para la mano abierta
	Abierta_Filtrada.Menique = Mediana_Buffer(CAL_Mano_Abierta.Menique, CAL_SIZE);
	Abierta_Filtrada.Anular = Mediana_Buffer(CAL_Mano_Abierta.Anular, CAL_SIZE);
	Abierta_Filtrada.Medio = Mediana_Buffer(CAL_Mano_Abierta.Medio, CAL_SIZE);
	Abierta_Filtrada.Indice = Mediana_Buffer(CAL_Mano_Abierta.Indice, CAL_SIZE);
	Abierta_Filtrada.Pulgar = Mediana_Buffer(CAL_Mano_Abierta.Pulgar, CAL_SIZE);

		// 2. Para la mano cerrada
	Cerrada_Filtrada.Menique = Mediana_Buffer(CAL_Mano_Cerrada.Menique, CAL_SIZE);
	Cerrada_Filtrada.Anular = Mediana_Buffer(CAL_Mano_Cerrada.Anular, CAL_SIZE);
	Cerrada_Filtrada.Medio = Mediana_Buffer(CAL_Mano_Cerrada.Medio, CAL_SIZE);
	Cerrada_Filtrada.Indice = Mediana_Buffer(CAL_Mano_Cerrada.Indice, CAL_SIZE);

	// El pulgar es un caso especial
	// Con la mano cerrada: queda sobre los dedos
	// Con la mano abierta y cerrando el pulgar se tiene mayor rango
	Cerrada_Filtrada.Pulgar = Mediana_Buffer(CAL_Pulgar_Cerrado.Pulgar, CAL_SIZE);


	// Calculo los rangos de movimiento de los dedos
	CAL_rango.Menique = modulo(Abierta_Filtrada.Menique, Cerrada_Filtrada.Menique, &(CAL_Minimos.Menique));
	CAL_rango.Anular = modulo(Abierta_Filtrada.Anular, Cerrada_Filtrada.Anular, &(CAL_Minimos.Anular));
	CAL_rango.Medio = modulo(Abierta_Filtrada.Medio, Cerrada_Filtrada.Medio, &(CAL_Minimos.Medio));
	CAL_rango.Indice = modulo(Abierta_Filtrada.Indice, Cerrada_Filtrada.Indice, &(CAL_Minimos.Indice));
	CAL_rango.Pulgar = modulo(Abierta_Filtrada.Pulgar, Cerrada_Filtrada.Pulgar, &(CAL_Minimos.Pulgar));

}

void MDE_Calibrar(volatile uint8_t *main_status) {
	uint8_t key = 0;
	uint8_t f_ready = 0;
	// Estados
	static volatile uint8_t estado_calibrar = CALIB_RESET;
	static volatile uint8_t estado_secuencia = NO_SEQUENCE;

	// (protección)
	// caso: el ADQ de la otra MDE está muestreando.
	if( (*main_status == BUSY) && (estado_calibrar == CALIB_INACTIVE) ){
		return;
	}

	// MdE: medición del ADC y transmisión de datos
	switch (estado_calibrar) {

		case CALIB_RESET:
			estado_calibrar = CALIB_INACTIVE;
			estado_secuencia = NO_SEQUENCE;
			f_ready = 0;
			CAL_inxBuffers = 0;
			//Default_Rangos();
			break;

		case CALIB_INACTIVE:

			key = GetKey();

			// caso: comando para iniciar la calibración
			if ( ( command == CALIBRATE ) || ( key == SW1 ) ) {
				command = NO_COMMAND;
				estado_calibrar = CALIB_PUSH;
				estado_secuencia = WAIT_OPEN_HAND;
				*main_status = BUSY;

				LCD_DisplayMsg("> Abra la mano  ", LCD_RENGLON_1, 0);
				LCD_DisplayMsg("> y presione SW1", LCD_RENGLON_2, 0);
				LED_Set(LED_STICK, LED_STICK_ON);	// LED del stick, testigo de la calibración
			}
			break;

		case CALIB_PUSH:

			key = GetKey();

			if( key == SW1 ){

				if( estado_secuencia == WAIT_OPEN_HAND ){
					estado_secuencia = SAMPLE_OPEN_HAND;
					LCD_DisplayMsg("> CALIBRANDO.   ", LCD_RENGLON_1, 0);
					LCD_DisplayMsg("> Mano abierta. ", LCD_RENGLON_2, 0);
					LED_Set(RGB_B, LED_RGB_ON);		// LED Azul, testigo del muestreo
				}
				else if( estado_secuencia == WAIT_CLOSED_HAND ){
					estado_secuencia = SAMPLE_CLOSED_HAND;
					LCD_DisplayMsg("> CALIBRANDO.   ", LCD_RENGLON_1, 0);
					LCD_DisplayMsg("> Mano cerrada. ", LCD_RENGLON_2, 0);
					LED_Set(RGB_B, LED_RGB_ON);		// LED Azul, testigo del muestreo
				}
				else if( estado_secuencia == WAIT_CLOSED_THUMB ){
					estado_secuencia = SAMPLE_CLOSED_THUMB;
					LCD_DisplayMsg("> CALIBRANDO.   ", LCD_RENGLON_1, 0);
					LCD_DisplayMsg("> Pulgar cerrado", LCD_RENGLON_2, 0);
					LED_Set(RGB_B, LED_RGB_ON);		// LED Azul, testigo del muestreo
				}

				estado_calibrar = CALIB_SAMPLING;

				f_ADC_Samples_rdy = 0;
				ResetBuffers();
				CAL_inxBuffers = 0;		// por las dudas
				f_Start_Calibration = 1;

			}
			break;

		case CALIB_SAMPLING:
			// caso: muestra lista, la enlisto en los vectores de calibración
			if (f_ADC_Samples_rdy) {
				f_ADC_Samples_rdy = 0;
				f_ready = Preparar_Calibracion(estado_secuencia);
			}

			// caso: se tienen los datos
			if ( f_ready ) {
				f_StopSampling = 1;
				f_ready = 0;

				if( estado_secuencia == SAMPLE_OPEN_HAND ){
					estado_calibrar = CALIB_PUSH;
					estado_secuencia = WAIT_CLOSED_HAND;
					LED_Set(RGB_B, LED_RGB_OFF);

					LCD_DisplayMsg("> Cierre la mano", LCD_RENGLON_1, 0);
					LCD_DisplayMsg("> y presione SW1", LCD_RENGLON_2, 0);
				}
				if( estado_secuencia == SAMPLE_CLOSED_HAND ){
					estado_calibrar = CALIB_PUSH;
					estado_secuencia = WAIT_CLOSED_THUMB;
					LED_Set(RGB_B, LED_RGB_OFF);

					LCD_DisplayMsg("> Cierre pulgar ", LCD_RENGLON_1, 0);
					LCD_DisplayMsg("> y presione SW1", LCD_RENGLON_2, 0);
				}
				if( estado_secuencia == SAMPLE_CLOSED_THUMB ){
					estado_calibrar = CALIB_PROCESS;
					estado_secuencia = NO_SEQUENCE;
					LED_Set(RGB_B, LED_RGB_OFF);
				}
			}
			break;

		case CALIB_PROCESS:

			Calibrar();
			U1_PushTx('#');
			U1_PushTx('R');
			U1_PushTx('A');
			U1_PushTx('N');
			U1_PushTx('G');
			U1_PushTx('O');
			U1_PushTx('$');
			EnviarMano(CAL_rango);

			estado_calibrar = CALIB_DONE;

			LCD_DisplayMsg("Fin Calibracion ", LCD_RENGLON_1, 0);
			LCD_DisplayMsg("> presione SW1  ", LCD_RENGLON_2, 0);
			break;

		case CALIB_DONE:

			key = GetKey();

			if ( key == SW1 ){
				estado_calibrar = CALIB_INACTIVE;
				*main_status = FREE;
				// para ignorar comandos que hayan llegado en el proceso de calibrar
				command = NO_COMMAND;

				LED_Set(LED_STICK, LED_STICK_OFF);
				LCD_DisplayMsg("> ADQ. INACTIVO.", LCD_RENGLON_1, 0);
				LCD_DisplayMsg("> TPO Manotronic", LCD_RENGLON_2, 0);
			}
			break;

		default:
			estado_calibrar = CALIB_RESET;
			break;
	}
}
